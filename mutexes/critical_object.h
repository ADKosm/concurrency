//
// Created by alex on 25.06.19.
//

#ifndef CONCURRENCY_CRITICAL_OBJECT_H
#define CONCURRENCY_CRITICAL_OBJECT_H

#include <atomic>
#include <assert.h>

class CriticalObject {
public:
    CriticalObject() {
        value.store(0);
    }

    void action() {
        for (int i = 0; i < 10; i++) {
            assert(value.fetch_add(1) == i);
        }

        assert(value.load() == 10);

        for (int i = 10; i > 0; i--) {
            assert(value.fetch_sub(1) == i);
        }

        assert(value.load() == 0);
    }

private:
    std::atomic_int value;
};

#endif //CONCURRENCY_CRITICAL_OBJECT_H
