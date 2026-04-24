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
    v.insert(1, 7);
    assert(v.size() == 4);

    // Act + Assert: insert at the end should increase size
    v.insert(v.size(), 100);
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

void test_insert_shifts_elements_and_throws_out_of_range(){
    // Arrange: create an empty vector
    rtb::Vector<int> v;

    // Act: insert elements at beginning, middle, and end
    v.insert(0, 5);           // [5]
    v.insert(0, 10);          // [10, 5]
    v.insert(1, 20);          // [10, 20, 5]
    v.insert(1, 15);          // [10, 15, 20, 5]
    v.insert(v.size(), 25);   // [10, 15, 20, 5, 25]

    // Assert: insert should increase size and keep correct order
    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 15);
    assert(v[2] == 20);
    assert(v[3] == 5);
    assert(v[4] == 25);
    assert(!v.empty());

    // Act: try to insert at invalid position
    bool exceptionThrown = false;
    try {
        v.insert(100, 1);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    // Assert: insert should throw std::out_of_range for invalid position
    assert(exceptionThrown);
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
    test_insert_shifts_elements_and_throws_out_of_range();

    std::cout << "All manual unit tests passed!\n";
    return 0;
}