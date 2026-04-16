cmake_minimum_required(VERSION 3.15)
project(StackAndQueue CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(test_stack
    tests/test_stack.cpp
    src/stack.cpp
)

add_executable(test_queue
    tests/test_queue.cpp
    src/queue.cpp
)