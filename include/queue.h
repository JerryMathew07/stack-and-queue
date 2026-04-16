#pragma once

#include <stdexcept>
#include <cstddef>

// Array-based Queue (circular buffer, fixed capacity)

class ArrayQueue {
    public:
        explicit ArrayQueue(std::size_t capacity);
        ~ArrayQueue();

        void enqueue(int value);
        void dequeue();

        int front() const;
        int back() const;
        bool empty() const;
        bool full() const;
        std::size_t size() const;
        std::size_t capacity() const;

        ArrayQueue(const ArrayQueue&) = delete;
        ArrayQueue& operator=(const ArrayQueue&) = delete;

    private:
        int* data_;
        std::size_t capacity_;
        std::size_t head_;
        std::size_t tail_;
        std::size_t size_;
};

// Linked-list-based Queue (unbounded)

class LinkedQueue{
    public:
        LinkedQueue();
        ~LinkedQueue();

        void enqueue(int value);
        void dequeue();
        int front() const;
        int back() const;
        bool empty() const;
        std::size_t size() const;

        LinkedQueue(const LinkedQueue&) = delete;
        LinkedQueue& operator=(const LinkedQueue&) = delete;

    private:
        struct Node {
            int data;
            Node* next;
            Node(int val) : data(val), next(nullptr) {} 
        };

        Node* head_;
        Node* tail_;
        std::size_t size_;
};