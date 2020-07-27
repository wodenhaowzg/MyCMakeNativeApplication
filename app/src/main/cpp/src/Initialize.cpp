//
// Created by 王志国 on 18/8/23.
//

#include <android/log.h>
#include <string>
#include "ChildJni.h"
#include "SecondChildJni.h"

#define LOG_TAG "wzg"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO , LOG_TAG , __VA_ARGS__)

std::string mClassPaths[] = {
        "com/azx/jni/MyFirstJni",
        "com/azx/jni/MySecondJni"
};

JNINativeMethod mFirstChildMethods[] = {
        {"initialize",           "(Lcom/azx/jni/MyFirstJni;)Z", (void *) ChildJni::initialize},
        {"unInitialize",         "()V",                                (void *) ChildJni::unInitialize},
        {"firstOneNativeMethod", "()V",                                (void *) ChildJni::childFirstNativeFun},
        {"firstTwoNativeMethod", "(J)V",                               (void *) ChildJni::childSecondNativeFun},
};

JNINativeMethod mSecondChildMethods[] = {
        {"initialize",            "(Lcom/azx/jni/MySecondJni;)Z", (void *) SecondChildJni::initialize},
        {"unInitialize",          "()V",                                 (void *) SecondChildJni::unInitialize},
        {"secondOneNativeMethod", "()V",                                 (void *) SecondChildJni::secondChildFirstNativeFun},
        {"secondTwoNativeMethod", "(J)V",                                (void *) SecondChildJni::secondChildSecondNativeFun},
};

JNINativeMethod *mMethods[] = {
        mFirstChildMethods,
        mSecondChildMethods
};

int MethodsCount[] = {
        sizeof(mFirstChildMethods),
        sizeof(mSecondChildMethods),
};


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *mEnv = nullptr;
    if (vm->GetEnv((void **) &mEnv, JNI_VERSION_1_6) != JNI_OK) {
        LOGI("JNI_OnLoad.... failed!");
        return JNI_ERR;
    }

    LOGI("JNI_OnLoad.... failed!");
    int methodLen = sizeof(mMethods) / sizeof(mMethods[0]);
    for (int i = 0; i < methodLen; ++i) {
        jclass tempClass = mEnv->FindClass(mClassPaths[i].c_str());
        if (tempClass == nullptr) {
            continue;
        }

        JNINativeMethod *tempMethodObj = mMethods[i];
        int len = MethodsCount[i] / sizeof(tempMethodObj[0]);
        if (mEnv->RegisterNatives(tempClass, tempMethodObj, len) < 0) {
            return false;
        }
        mEnv -> DeleteLocalRef(tempClass);
    }
    ttt_jni::InitGlobalJniVariables(vm);
    LOGI("JNI_OnLoad.... success!");
    return JNI_VERSION_1_6;
}