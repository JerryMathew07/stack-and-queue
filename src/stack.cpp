#include "stack.h"

// ArrayStack

ArrayStack::ArrayStack(std::size_t capacity)
    : data_(new int[capacity]), capacity_(capacity), size_(0) {}

ArrayStack::~ArrayStack() { delete[] data_;}

void ArrayStack::push(int value){
    if (full())
        throw std::overflow_error("ArrayStack::push - stack is full");
    data_[size_++] = value;
}

void ArrayStack::pop() {
    if (empty())
        throw std::underflow_error("ArrayStack::pop - stack is empty");
    --size_;
}

int ArrayStack::top() const {
    if (empty())
        throw std::underflow_error("ArrayStack::top - stack is empty");
    return data_[size_ - 1];
}

bool ArrayStack::empty() const { return size_ == 0; }
bool ArrayStack::full() const { return size_ == capacity_; }
std::size_t ArrayStack::size() const { return size_; }
std::size_t ArrayStack::capacity() const { return capacity_; }

// LinkedStack

LinkedStack::LinkedStack(): head_(nullptr), size_(0) {}

LinkedStack::~LinkedStack(){
    while (head_){
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
}

void LinkedStack::push(int value){
    Node* node = new Node(value);
    node->next = head_;
    head_ = node;
    ++size_;
}

void LinkedStack::pop(){
    if (empty())
        throw std::underflow_error("LinkedStack::pop - stack is empty");
    Node* tmp = head_;
    head_ = head_->next;
    delete tmp;
    --size_;
}

int LinkedStack::top() const {
    if (empty())
        throw std::underflow_error("LinkedStack::top - stack is empty");
    return head_->data;
}

bool LinkedStack::empty() const { return size_ == 0; }
std::size_t  LinkedStack::size() const { return size_; }