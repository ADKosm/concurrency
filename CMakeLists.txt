cmake_minimum_required(VERSION 3.14)
project(concurrency)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(peterson_lock mutexes/peterson_lock.h mutexes/peterson_lock_test.cpp mutexes/critical_object.h mutexes/filter_lock.h mutexes/filter_lock_test.cpp)
add_executable(filter_lock mutexes/critical_object.h mutexes/filter_lock.h mutexes/filter_lock_test.cpp)