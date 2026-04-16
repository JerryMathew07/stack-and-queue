#include "queue.h"

//ArrayQueue

ArrayQueue::ArrayQueue(std::size_t capacity)
    : data_(new int[capacity + 1])
    , capacity_(capacity + 1)
    , head_(0), tail_(0), size_(0) {}

ArrayQueue::~ArrayQueue() { delete[] data_; }

void ArrayQueue::enqueue(int value) {
    if (full())
        throw std::overflow_error("ArrayQueue::enqueue - queue is full");
    data_[tail_] = value;
    tail_ = (tail_ + 1) % capacity_;
    ++size_;
}

void ArrayQueue::dequeue() {
    if (empty())
        throw std::underflow_error("ArrayQueue::dequeue - queue is empty");
    head_ = (head_ + 1) % capacity_;
    --size_;
}

int ArrayQueue::front() const {
    if (empty())
        throw std::underflow_error("ArrayQueue::front - queue is empty");
    return data_[head_];
}

int ArrayQueue::back() const {
    if (empty())
        throw std::underflow_error("ArrayQueue::back - queue is empty");
    return data_[(tail_ + capacity_ - 1) % capacity_];
}

bool ArrayQueue::empty() const { return size_ == 0; }
bool ArrayQueue::full() const { return size_ == capacity_ - 1; }
std::size_t ArrayQueue::size() const { return size_; }
std::size_t ArrayQueue::capacity() const { return capacity_ - 1; }

// LinkedQueue

LinkedQueue::LinkedQueue() : head_(nullptr), tail_(nullptr), size_(0) {}

LinkedQueue::~LinkedQueue(){
    while(head_){
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
}

void LinkedQueue::enqueue(int value){
    Node* node = new Node(value);
    if (tail_) 
        tail_->next = node;
    else 
        head_ = node;

    tail_ = node;
    ++size_;
}

void LinkedQueue::dequeue(){
    if (empty())
        throw std::underflow_error("LinkedQueue:dequeue - queue is empty");
    Node* tmp = head_;
    head_ = head_->next;
    if(!head_) tail_ = nullptr; 
    delete tmp;
    --size_;
}

int LinkedQueue::front() const {
    if (empty())
        throw std::underflow_error("LinkedQueue::front - queue is empty");
    return head_->data;
}

int LinkedQueue::back() const {
    if (empty())
        throw std::underflow_error("LinkedQueue::back - queue is empty");
    return tail_->data;
}

bool LinkedQueue::empty() const { return size_ == 0; }
std::size_t LinkedQueue::size() const { return size_; }