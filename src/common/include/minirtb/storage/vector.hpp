#pragma once
#include <iostream>
#include <exception>

namespace rtb {

#define VECTOR_CAPACITY_FACTOR 2

template <typename T>
class Vector {
private: 
    T*     data_;
    size_t capacity_;
    size_t size_;

    void reallocate(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    Vector() {
        data_     = nullptr;
        capacity_ = 0;
        size_     = 0; 
    }

    Vector(const Vector& other) {
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i){
            data_[i] = other.data_[i];
        }
        capacity_ = other.capacity_;
        size_     = other.size_;
    }

    Vector(Vector&& other) {
        data_     = other.data_;
        capacity_ = other.capacity_;
        size_     = other.size_;

        other.data_     = nullptr;
        other.capacity_ = 0;
        other.size_     = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            for (size_t i = 0; i < other.size_; ++i){
                data_[i] = other.data_[i];
            }
            capacity_ = other.capacity_;
            size_     = other.size_;
        }
        return *this;
    }

    Vector& operator=(Vector&& other) {
        if (this != &other) {
            delete[] data_;
            data_     = other.data_;
            capacity_ = other.capacity_;
            size_     = other.size_;

            other.data_     = nullptr;
            other.capacity_ = 0;
            other.size_     = 0;
        }
        return *this;
    }
    
    T* data(){
        return data_;
    }

    const T* data() const {
        return data_;
    }
    
    size_t size() const {
        return size_;
    }

    size_t capacity() const{
        return capacity_;
    }

    bool empty() const {
        return size_ == 0; 
    }

    T& at(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range;
        }
        return data_[pos];
    }

    T& at(size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range;
        }
        return data_[pos];
    }

    T& operator[](size_t pos) {
        return data_[pos];
    }

    T& operator[](size_t pos) const {
        return data_[pos];
    }

    void pushBack(T value) {
        if (size_ == capacity_){
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }
        data_[size_++] = value; 
    }

    void insert(int pos, T value) {
        if (size_ == capacity_){
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }
        for (size_t i = size_; i > pos; --i) {
            data_[i] = data_[i - 1];
        }
        data_[pos] = value;
        ++size_;
    }


};
}























