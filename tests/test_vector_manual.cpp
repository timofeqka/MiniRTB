#include <iostream>
#include <cassert>
#include <stdexcept>
#include "minirtb/storage/vector.hpp"

void test_constructor_initial_state(){
    // Arrange + Act: create an empty vector
    rtb::Vector<int> v;

    // Assert: new vector should have no allocated storage and no elements
    assert(v.data() == nullptr);
    assert(v.capacity() == 0);
    assert(v.size() == 0);

    assert(v.empty() == true);
}

void test_size_updates_after_pushBack_and_insert(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Assert: initial size should be zero
    assert(v.size() == 0);

    // Act + Assert: pushBack should increase size
    v.pushBack(10);
    assert(v.size() == 1);

    v.pushBack(20);
    assert(v.size() == 2);

    // Act + Assert: insert at the beginning should increase size
    v.insert(0, 5);
    assert(v.size() == 3);

    // Act + Assert: insert in the middle should increase size
    v.insert(v.begin() + 1, 7);
    assert(v.size() == 4);

    // Act + Assert: insert at the end should increase size
    v.insert(v.end(), 100);
    assert(v.size() == 5);
}

void test_capacity_grows_when_full(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Assert: initial capacity should be zero
    assert(v.capacity() == 0);
    assert(v.capacity() >= v.size());

    // Act + Assert: first pushBack should allocate capacity 1
    v.pushBack(10);
    assert(v.capacity() == 1);
    assert(v.capacity() >= v.size());

    // Act + Assert: capacity should double when vector becomes full
    v.pushBack(20);
    assert(v.capacity() == 2);

    v.pushBack(30);
    assert(v.capacity() == 4);

    // Act + Assert: capacity should not change while there is free space
    v.pushBack(40);
    assert(v.capacity() == 4);

    // Act + Assert: capacity should grow again when full
    v.pushBack(50);
    assert(v.capacity() == 8);

    // Assert: capacity should always be greater than or equal to size
    assert(v.capacity() >= v.size());
}

void test_empty_reflects_size(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Assert: new vector should be empty
    assert(v.empty());
    assert(v.size() == 0);

    // Act: add one element
    v.pushBack(10);

    // Assert: vector should no longer be empty
    assert(!v.empty());
    assert(v.size() == 1);
}

void test_data_returns_contiguous_storage(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Assert: empty vector should not have allocated storage
    assert(v.data() == nullptr);
    
    // Act: add first element
    v.pushBack(10);

    // Assert: storage should now be allocated and contain the first element
    assert(v.data() != nullptr);
    assert(v.data()[0] == 10);

    // Act: add second element
    v.pushBack(20);

    // Assert: data should point to contiguous storage
    assert(v.data()[0] == 10);
    assert(v.data()[1] == 20);

    // Assert: data() and operator[] should refer to the same memory
    assert(v.data()[0] == v[0]);
    assert(v.data()[1] == v[1]);
    assert(&v[0] == v.data());
}

void test_subscript_operator_read_write(){
    // Arrange: create a vector with two elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);

    // Assert: operator[] should allow reading elements
    assert(v.operator[](0) == 10);
    assert(v.operator[](1) == 20);

    // Act: modify elements through operator[]
    v[0] = 100;
    v[1] = 200;

    // Assert: operator[] should allow writing elements
    assert(v[0] == 100);
    assert(v[1] == 200);
}

void test_at_returns_element_and_throws_out_of_range(){
    // Arrange: create a vector with two elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);

    // Assert: at() should return valid elements
    assert(v.at(0) == 10);
    assert(v.at(1) == 20);

    // Act: try to access an invalid index
    bool exceptionThrown = false;
    try {
        v.at(2);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    // Assert: at() should throw std::out_of_range for invalid index
    assert(exceptionThrown);
}

void test_pushBack_appends_elements(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Act: append two elements
    v.pushBack(10);
    v.pushBack(20);

    // Assert: elements should be appended in order
    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(!v.empty());
}

void test_insert_shifts_elements(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Act: insert elements at beginning, middle, and end
    v.insert(0, 5);             // [5]
    v.insert(0, 10);            // [10, 5]
    v.insert(v.begin() + 1, 20);// [10, 20, 5]
    v.insert(v.begin() + 1, 15);// [10, 15, 20, 5]
    v.insert(v.end(), 25);      // [10, 15, 20, 5, 25]

    // Assert: insert should increase size and keep correct order
    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 15);
    assert(v[2] == 20);
    assert(v[3] == 5);
    assert(v[4] == 25);
    assert(!v.empty());
}

void test_copy_constructor() {
    // Arrange: create an empty vector
    rtb::Vector<int> empty;

    // Act: copy the empty vector
    rtb::Vector<int> empty_copy(empty);

    // Assert: copied empty vector should also be empty
    assert(empty_copy.capacity() == 0);
    assert(empty_copy.size() == 0);
    assert(empty_copy.empty());

    // Arrange: create a vector with two elements
    rtb::Vector<int> v1;
    v1.pushBack(10);
    v1.pushBack(20);

    // Act: copy the populated vector
    rtb::Vector<int> v2(v1);

    // Assert: copied vector should have separate storage and the same values
    assert(v2.data() != v1.data());
    assert(v2.capacity() == v1.capacity());
    assert(v2.size() == v1.size());
    assert(v2[0] == v1[0]);
    assert(v2[1] == v1[1]);

    // Act: modify the copied vector
    v2[1] = 30; 

    // Assert: modifying the copy should not change the original vector
    assert(v1[1] == 20);
    assert(v2[1] == 30);
}

void test_move_constructor() {
    // Arrange: create a vector with two elements
    rtb::Vector<int> v1;

    v1.pushBack(10);
    v1.pushBack(20);

    // Act: move the vector into a new vector
    rtb::Vector<int> v2(std::move(v1));

    // Assert: moved-to vector should contain the original values
    assert(v2[0] == 10);
    assert(v2[1] == 20);
    assert(v2.size() == 2);
    assert(v2.capacity() == 2);
    assert(v2.data() != nullptr);

    // Assert: moved-from vector should be left empty
    assert(v1.data() == nullptr);
    assert(v1.size() == 0);
    assert(v1.capacity()  == 0);
    assert(v1.empty());
}

void test_copy_assignment_operator() {
    // Arrange: create an empty vector and another vector to assign into
    rtb::Vector<int> empty;
    rtb::Vector<int> empty_copy ;

    // Act: assign the empty vector
    empty_copy = empty;

    // Assert: assigned empty vector should also be empty
    assert(empty_copy.capacity() == 0);
    assert(empty_copy.size() == 0);
    assert(empty_copy.empty());

    // Arrange: create a vector with two elements
    rtb::Vector<int> v1;
    v1.pushBack(10);
    v1.pushBack(20);

    // Act: assign the populated vector into another vector
    rtb::Vector<int> v2;
    v2 = v1;

    // Assert: assigned vector should have separate storage and the same values
    assert(v2.data() != v1.data());
    assert(v2.capacity() == v1.capacity());
    assert(v2.size() == v1.size());
    assert(v2[0] == v1[0]);
    assert(v2[1] == v1[1]);

    // Act: modify the assigned vector
    v2[1] = 30; 

    // Assert: modifying the assigned vector should not change the original
    assert(v1[1] == 20);
    assert(v2[1] == 30);
}

void test_move_assignment_operator() {
    // Arrange: create a vector with two elements
    rtb::Vector<int> v1;
    v1.pushBack(10);
    v1.pushBack(20);

    // Act: move-assign the vector into another vector
    rtb::Vector<int> v2;
    v2 = std::move(v1);

    // Assert: moved-to vector should contain the original values
    assert(v2[0] == 10);
    assert(v2[1] == 20);
    assert(v2.size() == 2);
    assert(v2.capacity() == 2);
    assert(v2.data() != nullptr);

    // Assert: moved-from vector should be left empty
    assert(v1.data() == nullptr);
    assert(v1.size() == 0);
    assert(v1.capacity()  == 0);
    assert(v1.empty());
}

void test_errase() {
    // Arrange: create a vector with multiple elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);
    v.pushBack(40);
    v.pushBack(50);
    v.pushBack(60);

    size_t capacity_before = v.capacity();
    size_t size_before = v.size();

    // Act + Assert: erase first element and shift remaining elements left
    v.errase(0); // 20 30 40 50 60
    assert(v.capacity() == capacity_before);
    assert(v.size() == size_before - 1);
    assert(v[0] == 20); 

    // Act + Assert: erase middle element and keep capacity unchanged
    v.errase(2); // 20 30 50 60 
    assert(v.capacity() == capacity_before);
    assert(v.size() == size_before - 2);
    assert(v[2] == 50);

    // Act + Assert: erase last element and keep remaining values in order
    v.errase(3); // 20 30 50
    assert(v.capacity() == capacity_before);
    assert(v.size() == size_before - 3);
    assert(v[2] == 50);
}

void test_swap_basic() {
    // Arrange: create two vectors with different sizes and values
    rtb::Vector<int> a;
    a.pushBack(1);
    a.pushBack(2);
    a.pushBack(3);

    rtb::Vector<int> b;
    b.pushBack(10);
    b.pushBack(20);

    size_t a_size = a.size();
    size_t b_size = b.size();

    size_t a_capacity = a.capacity();
    size_t b_capacity = b.capacity();

    // Act: swap both vectors
    a.swap(b);

    // Assert: sizes, capacities, and values should be exchanged
    assert(a.size() == b_size);
    assert(b.size() == a_size);

    assert(a.capacity() == b_capacity);
    assert(b.capacity() == a_capacity);

    assert(a[0] == 10);
    assert(a[1] == 20);

    assert(b[0] == 1);
    assert(b[1] == 2);
    assert(b[2] == 3);
}

void test_pop_back() {
    // Arrange: create a vector with multiple elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    size_t capacity_before = v.capacity();
    size_t size_before = v.size();

    // Act: remove the last element
    v.pop_back();

    // Assert: size should decrease while capacity and remaining values stay valid
    assert(v.size() == size_before - 1);
    assert(v.capacity() == capacity_before);

    assert(v[0] == 10);
    assert(v[1] == 20);

    // Act + Assert: removing all elements should leave the vector empty
    v.pop_back();
    v.pop_back();

    assert(v.size() == 0);
    assert(v.capacity() == capacity_before);
}

void test_clear(){
    // Arrange: create a vector with allocated storage and elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    size_t capacity_before = v.capacity();

    // Act: clear all elements
    v.clear();

    // Assert: size should reset but capacity should be kept
    assert(v.size() == 0);
    assert(v.capacity() == capacity_before);

    // Act + Assert: vector should still be usable after clear
    v.pushBack(100);

    assert(v.size() == 1);
    assert(v[0] == 100);
} 

void test_emplace_back() {
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Act: construct elements at the end
    v.emplace_back(10);
    v.emplace_back(20);

    // Assert: emplaced values should be stored in order
    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 20);

    size_t capacity_before = v.capacity();

    // Act + Assert: adding another element should grow capacity when needed
    v.emplace_back(30);

    assert(v.capacity() > capacity_before);
    assert(v.size() == 3);
}

void test_front() {
    // Arrange: create a vector with multiple elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    // Assert: front() should return the first element
    assert(v.front() == 10);

    // Act: modify the first element through front()
    v.front() = 99;

    // Assert: the first stored value should be updated
    assert(v[0] == 99);
}

void test_back(){
    // Arrange: create a vector with multiple elements
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    // Assert: back() should return the last element
    assert(v.back() == 30);
    
    // Act: modify the last element through back()
    v.back() = 99;

    // Assert: the last stored value should be updated
    assert(v[2] == 99);
}

void test_front_back_empty_vector() {
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Act: try to read the front of an empty vector
    bool exceptionThrown = false;
    try {
        v.front();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    // Assert: front() should throw std::out_of_range
    assert(exceptionThrown);

    // Act: try to read the back of an empty vector
    exceptionThrown = false; 
    try {
        v.back();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    // Assert: back() should throw std::out_of_range
    assert(exceptionThrown);
}

void test_resize() {
    // Arrange: create a vector with existing values
    rtb::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);
    v.pushBack(40);

    size_t capacity_before_shrink = v.capacity();

    // Act: shrink the vector
    v.resize(2);

    // Assert: size should shrink while capacity and kept values remain
    assert(v.size() == 2);
    assert(v.capacity() == capacity_before_shrink);
    assert(v[0] == 10);
    assert(v[1] == 20);

    // Act: grow the vector
    v.resize(5);

    // Assert: new int elements should be value-initialized to zero
    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 0);
    assert(v[3] == 0);
    assert(v[4] == 0);

    size_t size_before_same = v.size();
    size_t capacity_before_same = v.capacity();

    // Act: resize to the current size
    v.resize(5);

    // Assert: size, capacity, and values should not change
    assert(v.size() == size_before_same);
    assert(v.capacity() == capacity_before_same);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 0);
    assert(v[3] == 0);
    assert(v[4] == 0);

    // Act + Assert: resizing to zero should remove all elements but keep capacity
    v.resize(0);

    assert(v.size() == 0);
    assert(v.capacity() == capacity_before_same);

    // Act + Assert: growing from zero should create default values
    v.resize(3);

    assert(v.size() == 3);
    assert(v[0] == 0);
    assert(v[1] == 0);
    assert(v[2] == 0);

    size_t capacity_before_grow = v.capacity();

    // Act + Assert: growing past capacity should reallocate
    v.resize(100);

    assert(v.size() == 100);
    assert(v.capacity() >= 100);
    assert(v.capacity() > capacity_before_grow);
    assert(v[0] == 0);
}

void test_begin_end_basic(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Assert: begin and end should match for an empty vector
    assert(v.begin() == v.end());

    // Act: add elements
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    // Assert: iterators should point to the first element and one past the last
    assert(*v.begin() == 10);
    assert(*(v.end() - 1) == 30);
}

void test_reserve() {
    // Arrange: create a vector with existing elements
    rtb::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);

    size_t size_before = v.size();
    size_t capacity_before = v.capacity();

    // Act: reserve more capacity than the vector currently has
    v.reserve(10);

    // Assert: capacity should grow while size and values stay the same
    assert(v.size() == size_before);
    assert(v.capacity() >= 10);
    assert(v[0] == 1);
    assert(v[1] == 2);

    size_t capacity_now = v.capacity();

    // Act: reserve less than the current capacity
    v.reserve(5);

    // Assert: capacity and size should not change
    assert(v.capacity() == capacity_now);
    assert(v.size() == size_before);
}


int main() {
    // Run all manual unit tests
    test_constructor_initial_state();
    test_size_updates_after_pushBack_and_insert();
    test_capacity_grows_when_full();
    test_empty_reflects_size();
    test_data_returns_contiguous_storage();
    test_subscript_operator_read_write();
    test_at_returns_element_and_throws_out_of_range();
    test_pushBack_appends_elements();
    test_insert_shifts_elements();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment_operator();
    test_move_assignment_operator();
    test_errase();
    //~Vector()
    //Vector(std::initializer_list<T> init)
    //Vector(size_t count, const T& value)
    test_begin_end_basic();
    //const_iterator begin()  const { return data_; }
    //const_iterator end()    const { return data_ + size_; }
    //const_iterator cbegin() const { return data_; }
    //const_iterator cend()   const { return data_ + size_; }
    test_front();
    test_back();
    test_front_back_empty_vector();
    //const T& front() const 
    //const T& back() const
    test_emplace_back();
    //void pushBack(T&& value)
    test_clear();
    test_resize();
    test_reserve();
    test_pop_back();
    test_swap_basic();
    //explicit Vector(size_t count)
    //Vector(InputIt first, InputIt last)
    //iterator insert(const_iterator pos, const T& value)
    //void insert(const_iterator pos, const T&& value)
    //insert &&
    //emplace
    //insert(pos, count, value)
    //insert(pos, first, last)
    //insert(pos, initList)
    //errase(first, last)


    std::cout << "All manual unit tests passed!\n";
    return 0;
}
