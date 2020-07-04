//
// Created by 王志国 on 18/8/22.
//
#include "BaseJni.h"
#include "ContainersTest.h"

#ifndef MYCPROJECT_ROOMJNI_H
#define MYCPROJECT_ROOMJNI_H


class ChildJni : BaseJni {
private:

    jmethodID mJavaChildFirstTestFun = nullptr;
    jmethodID mJavaChildSecondTestFun = nullptr;
    ContainersTest *mContainersTest;

    bool initJavaResources(JNIEnv *env, jobject javaScObj);

    void callJavaMethod(long arg1);

public:
    ThreadPool *pool = nullptr;

    ~ChildJni() {
        mJavaChildFirstTestFun = nullptr;
        mJavaChildSecondTestFun = nullptr;
        if (pool != nullptr) {
            delete pool;
            pool = nullptr;
        }

        if (mContainersTest != nullptr){
            delete mContainersTest;
            mContainersTest = nullptr;
        }
        LOGI("ChildJni destory...");
    };

    void initChild() {
        // 放在这里new而不放在构造函数里new，是因为更安全，若在初始化的时候异常
        // 析构函数会正常执行调用，不会导致内存泄漏
        // https://blog.csdn.net/lmb1612977696/article/details/77850378
        pool = new ThreadPool();
        pool->set_pool_size(5);

        mContainersTest = new ContainersTest();
        mContainersTest->init();
    }

    static bool initialize(JNIEnv *env, jobject thiz, jobject javaScObj);

    static void unInitialize(JNIEnv *env, jobject thiz);

    static void childFirstNativeFun(JNIEnv *env, jobject thiz);

    static void childSecondNativeFun(JNIEnv *env, jobject thiz, jlong arg1);

    void testThread(long javaArg);
};


#endif //MYCPROJECT_ROOMJNI_H
