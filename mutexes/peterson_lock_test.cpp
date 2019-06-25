//
// Created by alex on 25.06.19.
//

#include <iostream>
#include <assert.h>
#include <thread>
#include "peterson_lock.h"
#include "critical_object.h"

PetersonLock * mutex = nullptr;

void thread_work(CriticalObject* object, int thread_id) {
    assert(mutex != nullptr);

    for (int i = 0; i < 100; i++) {
        mutex->lock(thread_id);
        object->action();
        mutex->unlock(thread_id);
    }
}

int main() {
    auto obj = new CriticalObject();
    mutex = new PetersonLock();

    std::thread th1(thread_work, obj, 0);
    std::thread th2(thread_work, obj, 1);

    th1.join();
    th2.join();
}