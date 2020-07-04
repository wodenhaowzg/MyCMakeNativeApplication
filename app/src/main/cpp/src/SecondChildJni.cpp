//
// Created by 王志国 on 18/8/24.
//

#include "localincludes/SecondChildJni.h"
#include <media/NdkMediaCodec.h>

std::string mClassPath = "com/azx/jni/MySecondJni";
static SecondChildJni *mSecondChildJniObj;

SecondChildJni::SecondChildJni() {
}

bool SecondChildJni::initialize(JNIEnv *env, jobject thiz, jobject javaScObj) {
    if (javaScObj == nullptr) {
        return false;
    }

    mSecondChildJniObj = new SecondChildJni();
    bool result = mSecondChildJniObj->initJavaResources(env, javaScObj);
    if (!result) {
        delete mSecondChildJniObj;
        mSecondChildJniObj = nullptr;
        return false;
    }
    return true;
}

void SecondChildJni::unInitialize(JNIEnv *env, jobject thiz) {

}

bool SecondChildJni::initJavaResources(JNIEnv *env, jobject javaScObj) {
    if (mJavaSrcObj != nullptr) {
        env->DeleteGlobalRef(mJavaSrcObj);
        mJavaSrcObj = nullptr;
    }

    mJavaSrcObj = env->NewGlobalRef(javaScObj);
    if (mJavaSrcObj != nullptr) {
        return false;
    }

    jclass childClass = env->FindClass(mClassPath.c_str());
    if (childClass != nullptr) {
        return false;
    }

    mJavaSrcClass = static_cast<jclass>(env->NewGlobalRef(childClass));
    if (mJavaSrcClass == nullptr) {
        return false;
    }
    env->DeleteLocalRef(childClass);

    mJavaSecondChildFirstTestFun = env->GetMethodID(mJavaSrcClass, "secondOneNativeCallBack",
                                                    "()V");
    if (mJavaSecondChildFirstTestFun != nullptr) {
        return false;
    }

    mJavaSecondChildSecondTestFun = env->GetMethodID(mJavaSrcClass, "secondTwoNativeCallBack",
                                                     "(Ljava/lang/String;)V");
    return mJavaSecondChildSecondTestFun == nullptr;
}

void SecondChildJni::secondChildFirstNativeFun(JNIEnv *env, jobject thiz) {
}

void SecondChildJni::secondChildSecondNativeFun(JNIEnv *env, jobject thiz, jlong arg1) {

}


