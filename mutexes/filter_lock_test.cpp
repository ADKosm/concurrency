//
// Created by alex on 25.06.19.
//

#include <iostream>
#include <assert.h>
#include <thread>
#include "critical_object.h"
#include "filter_lock.h"

FilterLock * mutex = nullptr;

void thread_work(CriticalObject* object, int thread_id) {
    assert(mutex != nullptr);

    for (int i = 0; i < 1; i++) {
        mutex->lock(thread_id);
        object->action();
        mutex->unlock(thread_id);
    }
}

int main() {
    int N = 10;

    auto obj = new CriticalObject();
    mutex = new FilterLock(N);

    std::thread th1(thread_work, obj, 0);
    std::thread th2(thread_work, obj, 1);
    std::thread th3(thread_work, obj, 2);
    std::thread th4(thread_work, obj, 3);
    std::thread th5(thread_work, obj, 4);
    std::thread th6(thread_work, obj, 5);
    std::thread th7(thread_work, obj, 6);
    std::thread th8(thread_work, obj, 7);
    std::thread th9(thread_work, obj, 8);
    std::thread th10(thread_work, obj, 9);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();
}