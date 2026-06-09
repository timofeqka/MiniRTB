#pragma once
#include "vector.hpp" 
#include <stdexcept>
#include <utility>

namespace rtb {

#define EMPTY_INDEX -1

template <typename T>
class RingBuffer {
private:
    Vector<T> data_;    
    size_t    head_;
    size_t    tail_;
public:
    explicit RingBuffer(size_t size) {
        data_ = Vector<T>(size);
        head_ = EMPTY_INDEX;
        tail_ = EMPTY_INDEX;
    }
    
    RingBuffer(const RingBuffer& other) 
        : data_(other.data_), 
          head_(other.head_),
          tail_(other.tail_)
    {}

    RingBuffer(RingBuffer&& other) noexcept 
        : data_(std::move(other.data_)),
          head_(other.head_),
          tail_(other.tail_)
    {
        other.head_ = EMPTY_INDEX;
        other.tail_ = EMPTY_INDEX;
    }

    RingBuffer& operator=(const RingBuffer& other) {
        if (this != &other) {
            data_ = other.data_;
            head_ = other.head_;
            tail_ = other.tail_;
        }
        return *this;
    }

    RingBuffer& operator=(RingBuffer&& other) noexcept {
        if (this != &other) { 
            data_ = std::move(other.data_);
            head_ = other.head_;
            tail_ = other.tail_;

            other.head_ = EMPTY_INDEX;
            other.tail_ = EMPTY_INDEX;
        }
        return *this;
    }

    void push(const T& value) {
        if (head_ == tail_ && head_ != EMPTY_INDEX) {
            return;
        }

        if (head_ == EMPTY_INDEX) {
            head_ = 0;
            tail_ = 0;
        } 
        
        data_[tail_] = value;
        tail_ = (tail_ + 1) % data_.size();
    }

    void pop() {
        if (head_ == EMPTY_INDEX) {
            return;
        }

        head_ = (head_ + 1) % data_.size();

        if (head_ == tail_) {
            head_ = EMPTY_INDEX;
            tail_ = EMPTY_INDEX;
        } 
    }

//delete******************************
    // size_t head() const noexcept {
    //     return head_;
    // }

    // size_t tail() const noexcept {
    //     return tail_;
    // }
//delete******************************

    bool empty() const noexcept {
        return head_ == EMPTY_INDEX;
    }

    bool full() const {
        return head_ == tail_ && head_ != EMPTY_INDEX;
    }

    size_t size() const {
        if (empty()) {
            return 0; 
        } 
        else if (full()) {
            return data_.size();
        } 
        else if (tail_ > head_) {
            return tail_ - head_; 
        } 
        else {
            return data_.size() - head_ + tail_;
        }
    }

    size_t capacity() const noexcept {
        return data_.size();
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("Empty");
        }
        return data_[head_];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("Empty");
        }
        if (tail_ == 0) {
            return data_[data_.size() - 1];
        } else {
            return data_[tail_ - 1];
        }
    }

    T& operator[](size_t pos) {
        return data_[(head_ + pos) % data_.size()];
    }

    T& at(size_t pos){
        if (pos >= size()) {
            throw std::out_of_range("RingBuffer::at index out of range");
        }
        return data_[(head_ + pos) % data_.size()];
    }

    void clear() noexcept {
        head_ = EMPTY_INDEX;
        tail_ = EMPTY_INDEX;
    }
};
}
// 0 1  2 3 4 5 6 7 8 9
// 8 9 10 1 2 3 4 5 6 7              

// 0 1  2 3 4 5 6 7 8 9 10 11 
// 8 9 10       1 2 3 4 5 6 7           
//        T
//              H


// !push()
// emplace()
// !pop() 

// !front()
// !back()

// !empty()
// !full()
// !size()
// !capacity()

// !clear()

// !operator[]
// !at()

// try_push()
// try_pop()

// peek()