//
// Created by 王志国 on 18/10/29.
//

#ifndef MYCPROJECT_VECTORTEST_H
#define MYCPROJECT_VECTORTEST_H

#include <vector>
#include <unistd.h>
#include <sys/syscall.h>
#include "BaseJni.h"

class ContainersTest {

private:
    ThreadPool *mPools;

    void testVectorSort();

    void testSync();

public:

    ~ContainersTest() {
        if (mPools != nullptr) {
            delete mPools;
            mPools = nullptr;
        }
    }

    void init() {
        mPools = new ThreadPool();
        mPools->set_pool_size(100);
    };

    struct Student {
        std::string mName = "";
        int mAge = 0;
        int mScore = 0;
    };

    void startTest();
};


#endif //MYCPROJECT_VECTORTEST_H
