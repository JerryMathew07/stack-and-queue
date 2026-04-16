#pragma once

#include <stdexcept>
#include <cstddef>

// Array-based stack (fixed capacity)

class ArrayStack {
    public:
        explicit ArrayStack(std::size_t capacity);
        ~ArrayStack();

        void push(int value);
        int pop();
        int top() const;
        bool empty() const;
        bool full() const;
        std::size_t size() const;
        std::size_t capacity() const;

        ArrayStack(const ArrayStack&) = delete;
        ArrayStack& operator=(const ArrayStack&) = delete;

    private:
        int* data_;
        std::size_t capacity_;
        std::size_t size_;
};

// Linked-list-based Stack (unbounded)

class LinkedStack {
    public:
        LinkedStack();
        ~LinkedStack();

        void push(int value);
        void pop();
        int top() const;
        bool empty() const;
        std::size_t size() const;

        LinkedStack(const LinkedStack&) = delete;
        LinkedStack& operator=(const LinkedStack&) = delete;

    private:
        struct Node {
            int data;
            Node* next;
            Node(int val) : data(val), next(nullptr) {}
        };

        Node* head_;
        std::size_t size_;
};