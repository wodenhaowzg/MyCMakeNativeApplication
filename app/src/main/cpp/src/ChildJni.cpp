//
// Created by 王志国 on 18/8/22.
//

#include "ChildJni.h"
#include <unistd.h>
#include <sys/syscall.h>
#define SYS_gettid __NR_gettid

static std::string mChildClassPath = "com/azx/jni/MyFirstJni";
static ChildJni *mChildJniObj;

bool ChildJni::initialize(JNIEnv *env, jobject thiz, jobject javaScObj) {
    if (mChildJniObj != nullptr) {
        return false;
    }

    mChildJniObj = new ChildJni();
    mChildJniObj->initChild();
    bool result = mChildJniObj->initJavaResources(env, javaScObj);
    if (!result) {
        delete mChildJniObj;
        mChildJniObj = nullptr;
    }
    LOGI("initialize invoked.. %d", result);
    return result;
}

void ChildJni::unInitialize(JNIEnv *env, jobject thiz) {
    if (mChildJniObj != nullptr) {
        delete mChildJniObj;
        mChildJniObj = nullptr;
    }
    LOGI("unInitialize invoked.. ");
}

bool ChildJni::initJavaResources(JNIEnv *env, jobject javaScObj) {
    if (mJavaSrcObj != nullptr) {
        env->DeleteGlobalRef(mJavaSrcObj);
        mJavaSrcObj = nullptr;
    }

    mJavaSrcObj = env->NewGlobalRef(javaScObj);
    if (mJavaSrcObj == nullptr) {
        return false;
    }

    jclass childClass = env->FindClass(mChildClassPath.c_str());
    if (childClass == nullptr) {
        return false;
    }

    mJavaSrcClass = static_cast<jclass>(env->NewGlobalRef(childClass));
    if (mJavaSrcClass == nullptr) {
        return false;
    }
    env->DeleteLocalRef(childClass);

    mJavaChildFirstTestFun = env->GetMethodID(mJavaSrcClass, "firstNativeCallBack", "()V");
    if (mJavaChildFirstTestFun == nullptr) {
        return false;
    }

    mJavaChildSecondTestFun = env->GetMethodID(mJavaSrcClass, "secondNativeCallBack",
                                               "(Ljava/lang/String;)V");
    return mJavaChildSecondTestFun != nullptr;
}

void ChildJni::childFirstNativeFun(JNIEnv *env, jobject thiz) {
    LOGI("childFirstNativeFun invoked... thread id : ");
//    mChildJniObj->mContainersTest->startTest(); // 集合测试
}

void ChildJni::childSecondNativeFun(JNIEnv *env, jobject thiz, jlong arg1) {
    LOGI("childSecondNativeFun invoked... arg1 : %ld", (long) arg1);
}

void ChildJni::callJavaMethod(long javaArg) {
    JNIEnv *env = ttt_jni::AttachCurrentThreadIfNeeded();
    LOGI("callJavaMethod invoked... arg1 : %ld", javaArg);
    env->CallVoidMethod(mChildJniObj->mJavaSrcObj, mChildJniObj->mJavaChildFirstTestFun);
    mChildJniObj->testThread(javaArg);
}

void ChildJni::testThread(long javaArg) {
    if (pool == nullptr) {
        return;
    }
    pool->enqueue([](long as) {
        JNIEnv *env = ttt_jni::AttachCurrentThreadIfNeeded();
        int tid = (int) syscall(SYS_gettid);
        LOGI("callJavaMethod invoked... thread id : %d | arg1 : %ld", tid, as);
//        std::this_thread::sleep_for(std::chrono::seconds(2));
        env->CallVoidMethod(mChildJniObj->mJavaSrcObj, mChildJniObj->mJavaChildFirstTestFun);
        return as;
    }, javaArg);
}




