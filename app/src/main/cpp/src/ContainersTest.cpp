//
// Created by 王志国 on 18/10/29.
//

#include <ContainersTest.h>

/*
 * C++ 集合框架
 * 1.vector:类似JAVA的List集合，数组，不同步。
 *      * vector取值用[]与()的区别,[]不会检测索引是否有效，如果不存在会导致内存访问冲突，而()会检测索引的有效性，若无效会抛异常
 */

bool compareTo(const ContainersTest::Student &student1, const ContainersTest::Student &student2) {
    return student1.mAge > student2.mAge;
}

void ContainersTest::startTest() {
    // 测试集合是否是同步
    testSync();
//    testVectorSort();
}

void ContainersTest::testVectorSort() {
    std::vector<ContainersTest::Student> vec(10);
    std::stringstream ss;
    for (int i = 0; i < 30; ++i) {
        ContainersTest::Student student;
        ss << "test" << i;
        student.mName = ss.str();
        student.mAge = rand(); //随机数
        student.mScore = rand();
        vec.push_back(student);
        LOGI("vector add student... name : %s | age : %d | score : %d ", student.mName.c_str(),
             student.mAge, student.mScore);
        ss.str("");
        ss.clear();
    }

    std::sort(vec.begin(), vec.end(), compareTo);

    //Vector遍历方式1
//    for (std::vector<Student>::iterator it = vec.begin(); it != vec.end(); it++) {
//        LOGI("sort vector add student... name : %s | age : %d | score : %d ", it->mName.c_str(),
//             it->mAge, it->mScore);
//    }

    //Vector遍历方式2
//    for(int j = 0 ; j < vec.size() ; j++){
//        Student st = vec[j];
//        LOGI("sort vector add student... name : %s | age : %d | score : %d ", st.mName.c_str(),
//             st.mAge, st.mScore);
}


#include <mutex>

#define NUM_THREADS 500
std::mutex mut;
std::vector<std::string> mList(0);

// 添加锁进行同步
void add(std::vector<std::string>* list, const std::string &arg1) {
    mut.lock();
    list->push_back(arg1);
    mut.unlock();
}

// 线程的运行函数
void *testSyncThreadRun(std::vector<std::string>* list, bool isSync) {
    if (isSync){
        add(list, "aa");
    } else {
        list->emplace_back("aa");
    }
    usleep(100 * 1000);
    if (isSync){
        add(list, "aa");
    } else {
        list->emplace_back("aa");
    }
    return nullptr;
}

void ContainersTest::testSync() {
//    for (int i = 0; i < NUM_THREADS; ++i) {
//        mPools->enqueue([]() {
//            testSyncThreadRun(&mList, false);
//        });
//    }
//    sleep(10);
//    LOGI("wzgtest 最终添加记录条数：%d", mList.size());
}

