#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <new>
#include <stdexcept>
#include <utility>

namespace rtb {

#define VECTOR_CAPACITY_FACTOR 2

template <typename T>
class Vector {
private: 
    T*     data_;
    size_t capacity_;
    size_t size_;

    void reallocate(size_t newCapacity) {
        if (newCapacity < size_) { return; }

        T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

        for (size_t i = 0; i < size_; ++i) {
            new(newData + i) T(std::move(data_[i]));
            data[i].~T();
        }

        ::operator delete(data_);
        data_     = newData;
        capacity_ = newCapacity;
    }

public:
    using iterator       = T*; 
    using const_iterator = const T*;

    iterator       begin()        { return data_; }
    iterator       end()          { return data_ + size_; }
    const_iterator begin()  const { return data_; }
    const_iterator end()    const { return data_ + size_; }
    const_iterator cbegin() const { return data_; }
    const_iterator cend()   const { return data_ + size_; }


    Vector() {
        data_     = nullptr;
        capacity_ = 0;
        size_     = 0; 
    }

    explicit Vector(size_t count) {
        data_ = static_cast<T*>(::operator new(count * sizeof(T)));

        for (size_t i = 0; i < count; ++i) {
            new(data_ + i) T();
        }

        capacity_ = count; 
        size_ = count;
    }

    //to do
    // Vector(size_t count, const T& value) {
    //     size_ = count;
    //     capacity_ = count;
    // }

    Vector(std::initializer_list<T> init) {
        size_ = init.size();
        capacity_ = init.size();
        data_ = static_cast<T*>(::operator new(size_ * sizeof(T)));
        size_t i = 0;
        for (const auto& elem : init){
            new(data_ + i) T(elem); 
            ++i;
        }
    }

    template <typename InputIt>
    Vector(InputIt first, InputIt last) {
        size_t count = std::distance(first, last);
        size_ = count;
        capacity_ = count;
        data_ = static_cast<T*>(::operator new(count * sizeof(T)));
        size_t i = 0;
        for (auto it = first; it != last; ++it) {
            new(data + i) T(*it);
            ++i;
        }
    }

    ~Vector() {
        clear();
        ::operator delete(data_);
    }

    Vector(const Vector& other) {
        data_ = static_cast<T*>(::operator new(other.capacity_ * sizeof(T)));

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
            throw std::out_of_range("Vector::at index out of range");
        }
        return data_[pos];
    }

    T& at(size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at index out of range");
        }
        return data_[pos];
    }

    T& operator[](size_t pos) {
        return data_[pos];
    }

    T& operator[](size_t pos) const {
        return data_[pos];
    }

    T& front(){
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    T& back(){
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }
    
    template <typename...TArgs>
    T& emplace_back(TArgs&&...args){
        if (size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }
        new(data_ + size_) T(std::forward<TArgs>(args)...);
        return data_[size_++];
    }

    void pushBack(const T& value) {
        emplace_back(value);
    }

    void pushBack(T&& value) {
        emplace_back(std::move(value));
    }

    iterator insert(const_iterator pos, const T& value) {
        size_t index = pos - begin();

        if (size_ == capacity_){
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }

        for (size_t i = size_; i > index; --i) {
            new(data + i) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }

        new(data + index) T(value);
        ++size_;
        return begin() + index;
    }

    //to do
    // void insert(const_iterator pos, const T&& value) {

    // }

    void errase(size_t pos) {
        if (size_ > 0) {
                for (size_t i = pos; i < size_; ++i) {
                data_[i] = data_[i + 1];
            }
            --size_;
        }
    }

    void clear(){
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }

    void resize(size_t new_size) {
        if (size_ > new_size){
            for (size_t i = new_size; i < size_; ++i) {
                data_[i].~T();
            }
        }
        else if (size_ < new_size){
            if (capacity_ < new_size) { reallocate(new_size); }

            for (size_t i = size_; i < new_size; ++i) {
                new (&data_[i]) T();
            }
        } 
        size_ = new_size;
    }
    
    void reserve(size_t new_capacity){
        if (new_capacity > capacity_) { 
            reallocate(new_capacity); 
        }
    }

    void pop_back(){
        data_[size_ - 1].~T();
        --size_;
    }

    void swap(Vector& other){
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

//insert &&
//emplace
//insert(pos, count, value)
//insert(pos, first, last)
//insert(pos, initList)
//errase(first, last)
//vector( size_type count, const T& value);
};
} 
