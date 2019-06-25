//
// Created by alex on 25.06.19.
//

#ifndef CONCURRENCY_FILTER_LOCK_H
#define CONCURRENCY_FILTER_LOCK_H

class FilterLock {
public:
    FilterLock(int N) {
        n = N;
        levels = new int[N];
        victims = new int[N];
        for(int i = 0; i < N; i++) {
            levels[i] = 0;
        }
    }

    void lock(int thread_id) {
        for (int current_level = 1; current_level < n; current_level++) {
            levels[thread_id] = current_level;
            victims[current_level] = thread_id;

            bool is_higher_thread_exists;

            do {
                is_higher_thread_exists = false;
                for (int other_thread_id = 0; other_thread_id < n; other_thread_id++) {
                    if (levels[other_thread_id] >= current_level && other_thread_id != thread_id) {
                        is_higher_thread_exists = true;  // search all thread, which can try to enter this or higher level
                    }
                }
            } while (is_higher_thread_exists && victims[current_level] == thread_id);  // wait for other thread to enter all levels or wait to unvictim self
        }
    }

    void unlock(int thread_id) {
        levels[thread_id] = 0;
    }

private:
    volatile int n;
    volatile int *levels;  // thread_id -> level for this thread
    volatile int *victims;  // level -> victim for this level
};

#endif //CONCURRENCY_FILTER_LOCK_H
