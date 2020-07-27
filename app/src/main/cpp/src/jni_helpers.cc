/*
 *  Copyright 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#include "jni_helpers.h"

#include <pthread.h>
#include <android/log.h>


namespace ttt_jni {

    static JavaVM *g_jvm = nullptr;

    static pthread_once_t g_jni_ptr_once = PTHREAD_ONCE_INIT;

    // Key for per-thread JNIEnv* data.  Non-NULL in threads attached to |g_jvm| by
    // AttachCurrentThreadIfNeeded(), NULL in unattached threads and threads that
    // were attached by the JVM because of a Java->native call.
    static pthread_key_t g_jni_ptr;

    // Return a |JNIEnv*| usable on this thread or NULL if this thread is detached.
    JNIEnv *GetEnv() {
        void *env = nullptr;
        jint status = g_jvm->GetEnv(&env, JNI_VERSION_1_6);
        if (((env != nullptr) && (status == JNI_OK)) ||
            ((env == nullptr) && (status == JNI_EDETACHED))) {
            __android_log_print(ANDROID_LOG_ERROR, "jni_helpers",
                                "GetEnv error or thread is detached");
        }
        return reinterpret_cast<JNIEnv *>(env);
    }

    static void ThreadDestructor(void *prev_jni_ptr) {
        // This function only runs on threads where |g_jni_ptr| is non-NULL, meaning
        // we were responsible for originally attaching the thread, so are responsible
        // for detaching it now.  However, because some JVM implementations (notably
        // Oracle's http://goo.gl/eHApYT) also use the pthread_key_create mechanism,
        // the JVMs accounting info for this thread may already be wiped out by the
        // time this is called. Thus it may appear we are already detached even though
        // it was our responsibility to detach!  Oh well.
        if (!GetEnv())
            return;

        if (GetEnv() == prev_jni_ptr) {
            __android_log_print(ANDROID_LOG_ERROR, "jni_helpers", "detached jni in other thread");
        }
        jint status = g_jvm->DetachCurrentThread();

        if (status == JNI_OK) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers",
                                "Failed to detach thread: %d", status);
        }
        if (!GetEnv()) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers",
                                "Detaching was a successful no-op???");
        }
    }

    static void CreateJNIPtrKey() {
        if (!pthread_key_create(&g_jni_ptr, &ThreadDestructor)) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers",
                                "pthread_key_create");
        }
    }

    jint InitGlobalJniVariables(JavaVM *jvm) {
        if (!g_jvm) {
            __android_log_print(ANDROID_LOG_ERROR, "jni_helpers",
                                "InitGlobalJniVariables jvm is null");
        }
        g_jvm = jvm;

        if (!pthread_once(&g_jni_ptr_once, &CreateJNIPtrKey)) {
            __android_log_print(ANDROID_LOG_ERROR, "jni_helpers", "create pthread_once");
        }

        JNIEnv *jni = nullptr;
        if (jvm->GetEnv(reinterpret_cast<void **>(&jni), JNI_VERSION_1_6) != JNI_OK)
            return -1;

        return JNI_VERSION_1_6;
    }

    // Return a |JNIEnv*| usable on this thread.  Attaches to |g_jvm| if necessary.
    JNIEnv *AttachCurrentThreadIfNeeded() {
        JNIEnv *jni = GetEnv();
        if (jni) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers", "TLS has a JNIEnv* And  attached!");
            return jni;
        }
        if (!pthread_getspecific(g_jni_ptr)) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers",
                                "TLS has a JNIEnv* but not attached?");
        }

        JNIEnv *env = nullptr;

        if (g_jvm->AttachCurrentThread(&env, nullptr)) {
            __android_log_print(ANDROID_LOG_ERROR, "jni_helpers", "Failed to attach thread %p",
                                env);
        }
        if (env) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers",
                                "AttachCurrentThread handed back NULL!");
        }
        jni = reinterpret_cast<JNIEnv *>(env);
        if (!pthread_setspecific(g_jni_ptr, jni)) {
            __android_log_print(ANDROID_LOG_DEBUG, "jni_helpers",
                                "pthread_setspecific");
        }
        return jni;
    }

}
