//
// Created by 王志国 on 18/8/21.
//

#ifndef MYCPROJECT_BASEJNI_H
#define MYCPROJECT_BASEJNI_H

#include "Initialize.h"
#include "ThreadPool.h"
#include <string>
#include "jni_helpers.h"
#include <sstream>
#include <android/log.h>

#define LOG_TAG "wzg"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO , LOG_TAG , __VA_ARGS__)
using namespace progschj;

class BaseJni {
public:
    BaseJni() {
    }

    virtual ~BaseJni() {
        LOGI("BaseJni destory...");
        JNIEnv *env = ttt_jni::AttachCurrentThreadIfNeeded();
        if (mJavaSrcObj != nullptr) {
            env->DeleteGlobalRef(mJavaSrcObj);
            mJavaSrcObj = nullptr;
        }

        if (mJavaSrcClass != nullptr) {
            env->DeleteGlobalRef(mJavaSrcClass);
            mJavaSrcClass = nullptr;
        }
    }

protected:
    jobject mJavaSrcObj = nullptr;
    jclass mJavaSrcClass = nullptr;
};

#endif //MYCPROJECT_BASEJNI_H
