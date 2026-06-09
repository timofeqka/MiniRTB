#include <iostream>
#include <cassert>
#include <stdexcept>
#include "minirtb/storage/ring_buffer.hpp"

void test_constructor() {
    rtb::RingBuffer<int> rb(5);

    assert(rb.empty() == true);
    assert(rb.full() == false);

    assert(rb.size() == 0);
    assert(rb.capacity() == 5);


    bool exceptionThrown = false;
    try {
        rb.front();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    try {
        rb.back();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
}

void test_copy_constructor() {
    //Empty 
    rtb::RingBuffer<int> empty(5);
    rtb::RingBuffer<int> empty_copy(empty);

    assert(empty_copy.empty() == true);
    assert(empty_copy.full() == false);

    assert(empty_copy.size() == 0);
    assert(empty_copy.capacity() == 5);

    //With elements
    rtb::RingBuffer<int> rb1(5);
    rb1.push(1);
    rb1.push(2);
    rb1.push(3);

    rtb::RingBuffer<int> rb2(rb1);

    assert(rb1.size() == rb2.size());
    assert(rb1.capacity() == rb2.capacity());
    assert(rb1[0] == rb2[0]);
    assert(rb1[1] == rb2[1]);
    assert(rb1.front() == rb2.front());
    assert(rb1.back() == rb2.back());

    rb1[0] = 10;
    assert(rb1[0] == 10);
    assert(rb2[0] == 1);
}

void test_move_constructor() {
    rtb::RingBuffer<int> rb1(5);
    rb1.push(1);
    rb1.push(2);
    rb1.push(3);

    rtb::RingBuffer<int> rb2(std::move(rb1));

    assert(rb2.size() == 3);
    assert(rb2.capacity() == 5);
    assert(rb2[0] == 1);
    assert(rb2[2] == 3);
    assert(rb2.front() == rb2[0]);
    assert(rb2.back() == rb2[2]);

    assert(rb1.size() == 0);
    assert(rb1.capacity() == 0);
    assert(rb1.empty() == true);
    assert(rb1.full() == false);
}

void test_copy_assignment_operator() {
    //Empty 
    rtb::RingBuffer<int> empty(5);
    rtb::RingBuffer<int> empty_copy(0);

    empty_copy = empty;

    assert(empty_copy.empty() == true);
    assert(empty_copy.full() == false);

    assert(empty_copy.size() == 0);
    assert(empty_copy.capacity() == 5);

    //With elements
    rtb::RingBuffer<int> rb1(5);
    rb1.push(1);
    rb1.push(2);
    rb1.push(3);

    rtb::RingBuffer<int> rb2(0);

    rb2 = rb1;

    assert(rb1.size() == rb2.size());
    assert(rb1.capacity() == rb2.capacity());
    assert(rb1[0] == rb2[0]);
    assert(rb1[1] == rb2[1]);
    assert(rb1.front() == rb2.front());
    assert(rb1.back() == rb2.back());

    rb1[0] = 10;
    assert(rb1[0] == 10);
    assert(rb2[0] == 1);
}

void test_move_assignment_operator() { 
    rtb::RingBuffer<int> rb1(5);
    rb1.push(1);
    rb1.push(2);
    rb1.push(3);

    rtb::RingBuffer<int> rb2(0);

    rb2 = std::move(rb1);

    assert(rb2.size() == 3);
    assert(rb2.capacity() == 5);
    assert(rb2[0] == 1);
    assert(rb2[2] == 3);
    assert(rb2.front() == rb2[0]);
    assert(rb2.back() == rb2[2]);

    assert(rb1.size() == 0);
    assert(rb1.capacity() == 0);
    assert(rb1.empty() == true);
    assert(rb1.full() == false);
}

void test_push() {
    rtb::RingBuffer<int> rb(5);

    rb.push(1);
    assert(rb.size() == 1);
    assert(rb.front() == rb[0]);
    assert(rb.back() == rb[0]);

    rb.push(2);
    rb.push(3);
    assert(rb.size() == 3);
    assert(rb.front() == rb[0]);
    assert(rb[0] == 1);
    assert(rb[2] == 3);

    rb.push(4);
    rb.push(5);
    rb.push(6);
    assert(rb.size() == 5);
    assert(rb.front() == rb[0]);
    assert(rb.back() == rb[4]);
    // std::cout << rb.head() << "\n";
    // std::cout << rb.front() << "\n";
    // std::cout << rb.tail() << "\n";
    // std::cout << rb.back() << "\n";

    rb.pop();
    assert(rb.size() == 4);
    rb.push(7);
    // std::cout << rb[0] << rb[1] << rb[2] << rb[3] << rb[4] << "\n";
    // std::cout << rb.head() << "\n";
    // std::cout << rb.front() << "\n";
    // std::cout << rb.tail() << "\n";
    // std::cout << rb.back() << "\n";
}

void test_pop() {
    rtb::RingBuffer<int> rb(5);

    rb.pop();
    assert(rb.size() == 0);
    assert(rb.empty() == true);

    rb.push(1);
    rb.push(2);
    rb.pop();
    assert(rb.size() == 1);
    assert(rb.empty() == false);

    rb.pop();
    assert(rb.size() == 0);
    assert(rb.empty() == true);
    
}

void test_front() {
    rtb::RingBuffer<int> rb(5);

    bool exceptionThrown = false;
    try {
        rb.front();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    rb.push(1);
    rb.push(2);

    assert(rb.front() == rb[0]);
    assert(rb.front() == 1);

    rb.pop();
    assert(rb.front() == 2);

}

void test_back() {
    rtb::RingBuffer<int> rb(5);

    bool exceptionThrown = false;
    try {
        rb.back();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    rb.push(1);
    rb.push(2);

    assert(rb.back() == rb[1]);
    assert(rb.back() == 2);

    rb.pop();
    assert(rb.back() == rb.front());

    rb.push(3);
    rb.push(4);
    rb.push(5);
    rb.push(6);

    assert(rb.back() == 6);
}

void test_empty() {
    rtb::RingBuffer<int> rb(5);
    
    assert(rb.empty() == true);
    
    rb.push(1);
    assert(rb.empty() == false);

    rb.pop();
    assert(rb.empty() == true);
}

void test_full() {
    rtb::RingBuffer<int> rb(5);
    
    assert(rb.full() == false);
    
    rb.push(1);
    assert(rb.full() == false);

    rb.push(3);
    rb.push(4);
    rb.push(5);
    rb.push(6);
    assert(rb.full() == true);
}

void test_size() {
    rtb::RingBuffer<int> rb(5);

    assert(rb.size() == 0);

    rb.push(1);
    rb.push(2);
    rb.push(3);
    assert(rb.size() == 3);

    rb.push(4);
    rb.push(5);
    assert(rb.size() == 5);

    rb.pop();
    rb.push(6);
    assert(rb.size() == 5);
}

void test_capacity() {
    rtb::RingBuffer<int> rb(5);

    assert(rb.size() == 0);
    assert(rb.capacity() == 5);

    rb.push(1);
    rb.push(2);
    rb.push(3);
    assert(rb.size() == 3);
    assert(rb.capacity() == 5);

    rb.push(4);
    rb.push(5);
    assert(rb.size() == 5);
    assert(rb.capacity() == 5);

    rb.push(6);
    assert(rb.size() == 5);
    assert(rb.capacity() == 5);

    rb.pop();
    assert(rb.capacity() == 5);

}

void test_clear() {
    rtb::RingBuffer<int> rb(5);

    rb.push(1);
    rb.push(2);
    rb.push(3);
    assert(rb.size() == 3);
    assert(rb.capacity() == 5);
    assert(rb.front() == 1);
    assert(rb.back() == 3);

    rb.clear(); 
    assert(rb.size() == 0);
    assert(rb.capacity() == 5);
    assert(rb.empty() == true);
}

void test_operator() {
    rtb::RingBuffer<int> rb(3);

    rb.push(1);
    rb.push(2);
    rb.push(3);
    assert(rb[0] == 1);
    assert(rb[2] == 3);

    rb.pop();
    rb.push(4);
    assert(rb[0] == 2);
    assert(rb[2] == 4);
}

void test_at() {
    rtb::RingBuffer<int> rb(3);

    bool exceptionThrown = false;
    try {
        rb.at(1);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    rb.push(1);
    rb.push(2);
    rb.push(3);
    assert(rb.at(0) == 1);
    assert(rb.at(2) == 3);

    rb.pop();
    rb.push(4);
    assert(rb.at(0) == 2);
    assert(rb.at(2) == 4);
}


int main() {
    test_constructor();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment_operator();
    test_move_assignment_operator();

    test_push();
    test_pop();
    test_front();
    test_back();
    test_empty();
    test_full();
    test_size();
    test_capacity();
    test_clear();
    test_operator();
    test_at();

    std::cout << "All manual unit tests passed!\n";
    return 0;
}

