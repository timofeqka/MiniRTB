#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <new>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <type_traits>

namespace rtb {

template <typename T>
class Vector {
    static constexpr size_t VECTOR_CAPACITY_FACTOR = 2;
private: 
    T*     data_;
    size_t capacity_;
    size_t size_;

    void reallocate(size_t newCapacity) {
        if (newCapacity < size_) { return; }

        T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

        for (size_t i = 0; i < size_; ++i) {
            //TODO
            new(newData + i) T(std::move(data_[i]));
            data_[i].~T();
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

    Vector(size_t count, const T& value) {
        data_ = static_cast<T*>(::operator new(count * sizeof(T)));

        for (size_t i = 0; i < count; ++i) {
        //TODO
            new(data_ + i) T(value);
        }

        capacity_ = count; 
        size_ = count;
    }

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

    template 
    <
        typename InputIt,
        typename = std::enable_if_t<!std::is_integral_v<InputIt>>
    >
    Vector(InputIt first, InputIt last) {
        size_t count = std::distance(first, last);

        size_ = count;
        capacity_ = count;
        data_ = static_cast<T*>(::operator new(count * sizeof(T)));

        size_t i = 0;
        for (auto it = first; it != last; ++it) {
            new(data_ + i) T(*it);
            ++i;
        }
    }

    ~Vector() noexcept {
        clear();
        ::operator delete(data_);
    }

    Vector(const Vector& other) {
        data_ = static_cast<T*>(::operator new(other.capacity_ * sizeof(T)));

        for (size_t i = 0; i < other.size_; ++i){
            new(data_ + i) T(other.data_[i]);
        }

        capacity_ = other.capacity_;
        size_     = other.size_;
    }

    Vector(Vector&& other) noexcept {
        data_     = other.data_;
        capacity_ = other.capacity_;
        size_     = other.size_;

        other.data_     = nullptr;
        other.capacity_ = 0;
        other.size_     = 0;
    }

    Vector& operator=(const Vector& other) {
        // if (this != &other) {
        //     clear();
        //     ::operator delete(data_);

        //     data_ = static_cast<T*>(::operator new(other.capacity_ * sizeof(T)));

        //     for (size_t i = 0; i < other.size_; ++i){
        //         new(data_ + i) T(other.data_[i]);
        //     }

        //     capacity_ = other.capacity_;
        //     size_     = other.size_;
        // }
        // return *this;
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            ::operator delete(data_);

            data_     = other.data_;
            capacity_ = other.capacity_;
            size_     = other.size_;

            other.data_     = nullptr;
            other.capacity_ = 0;
            other.size_     = 0;
        }
        return *this;
    }

    T* data() noexcept {
        return data_;
    }

    const T* data() const noexcept {
        return data_;
    }
    
    size_t size() const noexcept {
        return size_;
    }

    size_t capacity() const noexcept {
        return capacity_;
    }

    bool empty() const noexcept {
        return size_ == 0; 
    }

    T& at(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at index out of range");
        }
        return data_[pos];
    }

    const T& at(size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Vector::at index out of range");
        }
        return data_[pos];
    }

    T& operator[](size_t pos) {
        return data_[pos];
    }

    const T& operator[](size_t pos) const {
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
    iterator emplace(const_iterator pos, TArgs&&...args) {
        // precondition: pos is a valid iterator from this Vector
        size_t index = pos - begin();

        if (size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }

        for (size_t i = size_; i > index; --i) {
            new(data_ + i) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }

        new(data_ + index) T(std::forward<TArgs>(args)...);
        ++size_;

        return begin() + index;
    }

    template <typename...TArgs>
    T& emplace_back(TArgs&&...args) {
        if (size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }
        new(data_ + size_) T(std::forward<TArgs>(args)...);
        return data_[size_++];
    }

    void push_back(const T& value) {
        emplace_back(value);
    }

    void push_back(T&& value) {
        emplace_back(std::move(value));
    }

    iterator insert(const_iterator pos, const T& value) {
        size_t index = pos - begin();

        if (size_ == capacity_){
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }

        for (size_t i = size_; i > index; --i) {
            new(data_ + i) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }

        new(data_ + index) T(value);
        ++size_;
        return begin() + index;
    }

    iterator insert(const_iterator pos, T&& value) {
        size_t index = pos - begin();
        
        if (size_ == capacity_){
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * VECTOR_CAPACITY_FACTOR;
            reallocate(newCapacity);
        }

        for (size_t i = size_; i > index; --i) {
            new(data_ + i) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }

        new(data_ + index) T(std::move(value));
        ++size_;
        return begin() + index;
    }

    iterator insert(const_iterator pos, size_t count, const T& value) {
        size_t index = pos - begin();

        if (count == 0) { return begin() + index; }

        if (size_ + count > capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_;

            while(newCapacity < size_ + count) {
                newCapacity *= VECTOR_CAPACITY_FACTOR;
            }
            
            reallocate(newCapacity);
        }

        for (size_t i = size_; i > index; --i) {
            new(data_ + i + count - 1) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }

        for (size_t i = 0; i < count; ++i) {
            new(data_ + index + i) T(value);
        }

        size_ += count;

        return begin() + index;
    }

    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_t index = pos - begin();
        size_t count = std::distance(first, last);

        if (count == 0) { return begin() + index; }

        if (size_ + count > capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_;

            while(newCapacity < size_ + count) {
                newCapacity *= VECTOR_CAPACITY_FACTOR;
            }

            reallocate(newCapacity);
        }

        for (size_t i = size_; i > index; --i) {
            new(data_ + i + count - 1) T(std::move(data_[i - 1]));
            data_[i - 1].~T();
        }

        size_t i = 0;
        for (auto it = first; it != last; ++it) {
            new(data_ + index + i) T(*it);
            ++i;
        }

        size_ += count;

        return begin() + index;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> init) {
        return insert(pos, init.begin(), init.end());
    }

    void erase(size_t pos) {
        // precondition: pos < size_

        if (size_ > 0) {
            for (size_t i = pos; i + 1 < size_; ++i) {
                data_[i] = data_[i + 1];
            }
            data_[size_ - 1].~T();
            --size_;
        }
    }

    iterator erase(const_iterator first, const_iterator last) {
        size_t indexFirst = first - begin();
        size_t indexLast = last - begin();

        if (indexFirst >= size_ || indexFirst >= indexLast) {
            return begin() + indexFirst;
        }

        size_t count = indexLast - indexFirst;

        for (size_t i = indexFirst; i + count < size_; ++i) {
            data_[i].~T();
            new(data_ + i) T(std::move(data_[i + count]));
        }

        for (size_t i = size_ - count; i < size_; i++) {
            data_[i].~T();
        }

        size_ -= count;

        return begin() + indexFirst;
    }

    void clear() noexcept {
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

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};
} 
