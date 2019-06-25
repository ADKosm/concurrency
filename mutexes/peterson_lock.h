//
// Created by alex on 25.06.19.
//

#ifndef CONCURRENCY_PETERSON_LOCK_H
#define CONCURRENCY_PETERSON_LOCK_H


class PetersonLock {
public:
    PetersonLock() = default;

    void lock(int thread_id) {
        flags[thread_id] = true;  // setup my flag
        victim = thread_id;  // I want to wait another thread
        while (flags[1-thread_id] && victim == thread_id) {}
    }
    void unlock(int thread_id) {
        flags[thread_id] = false;
    }

private:
    volatile bool flags[2];
    volatile int victim;
};


#endif //CONCURRENCY_PETERSON_LOCK_H
