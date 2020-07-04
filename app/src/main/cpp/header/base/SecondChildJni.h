//
// Created by 王志国 on 18/8/24.
//

#ifndef MYCPROJECT_SECONDCHILDJNI_H
#define MYCPROJECT_SECONDCHILDJNI_H

#include "BaseJni.h"
#

class SecondChildJni : BaseJni {

private:
    jmethodID mJavaSecondChildFirstTestFun = nullptr;
    jmethodID mJavaSecondChildSecondTestFun = nullptr;

    bool initJavaResources(JNIEnv *env, jobject javaScObj);
public:
    SecondChildJni();

    static bool initialize(JNIEnv *env, jobject thiz, jobject javaScObj);

    static void unInitialize(JNIEnv *env, jobject thiz);

    static void secondChildFirstNativeFun(JNIEnv *env, jobject thiz);

    static void secondChildSecondNativeFun(JNIEnv *env, jobject thiz, jlong arg1);

};

#endif //MYCPROJECT_SECONDCHILDJNI_H
