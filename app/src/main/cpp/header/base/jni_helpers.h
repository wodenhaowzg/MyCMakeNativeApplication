/*
 *  Copyright 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

// This file contain convenience functions and classes for JNI.
// Before using any of the methods, InitGlobalJniVariables must be called.

#ifndef SDK_ANDROID_SRC_JNI_JNI_HELPERS_H_
#define SDK_ANDROID_SRC_JNI_JNI_HELPERS_H_

#include <jni.h>
#include <map>
#include <string>
#include <vector>

namespace ttt_jni {

    jint InitGlobalJniVariables(JavaVM *jvm);

    // Return a |JNIEnv*| usable on this thread or NULL if this thread is detached.
    JNIEnv *GetEnv();

    JavaVM *GetJVM();

    // Return a |JNIEnv*| usable on this thread.  Attaches to |g_jvm| if necessary.
    JNIEnv *AttachCurrentThreadIfNeeded();

}
#endif  // SDK_ANDROID_SRC_JNI_JNI_HELPERS_H_
