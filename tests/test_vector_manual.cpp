#include <iostream>
#include <cassert>
#include <stdexcept>
#include "minirtb/storage/vector.hpp"

void test_begin() {
    rtb::Vector<int> v = {10, 20, 30};

    assert(*v.begin() == 10);

    *v.begin() = 99;
    assert(v[0] == 99);
}

void test_end() {
    rtb::Vector<int> v = {10, 20, 30};

    assert(v.end() - v.begin() == static_cast<std::ptrdiff_t>(v.size()));
    assert(*(v.end() - 1) == 30);
}

void test_cbegin() {
    const rtb::Vector<int> v = {10, 20, 30};

    assert(*v.cbegin() == 10);
    assert(v.cbegin() == v.begin());
}

void test_cend() {
    const rtb::Vector<int> v = {10, 20, 30};

    assert(v.cend() - v.cbegin() == static_cast<std::ptrdiff_t>(v.size()));
    assert(*(v.cend() - 1) == 30);
}

void test_constructor(){
    rtb::Vector<int> v;

    assert(v.data() == nullptr);
    assert(v.capacity() == 0);
    assert(v.size() == 0);

    assert(v.empty() == true);
}

void test_constructor_with_size() {
    rtb::Vector<int> v(5);

    assert(v.size() == 5);
    assert(v.capacity() >= 5);

    for (size_t i = 0; i < v.size(); ++i) {
        assert(v[i] == 0);
    }
}

void test_constructor_with_size_and_value() {
    rtb::Vector<int> v(4, 42);

    assert(v.size() == 4);
    assert(v.capacity() >= 4);

    for (size_t i = 0; i < v.size(); ++i) {
        assert(v[i] == 42);
    }
}

void test_constructor_with_initializer_list() {
    rtb::Vector<int> v = {10, 20, 30};

    assert(v.size() == 3);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
}

void test_constructor_with_range() {
    int arr[] = {5, 10, 15, 20};

    rtb::Vector<int> v(arr, arr + 4);

    assert(v.size() == 4);
    assert(v[0] == 5);
    assert(v[1] == 10);
    assert(v[2] == 15);
    assert(v[3] == 20);
}

void test_copy_constructor() {
    rtb::Vector<int> empty;
    rtb::Vector<int> empty_copy(empty);

    assert(empty_copy.capacity() == 0);
    assert(empty_copy.size() == 0);
    assert(empty_copy.empty());

    rtb::Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);

    rtb::Vector<int> v2(v1);

    assert(v2.data() != v1.data());
    assert(v2.capacity() == v1.capacity());
    assert(v2.size() == v1.size());
    assert(v2[0] == v1[0]);
    assert(v2[1] == v1[1]);

    v2[1] = 30; 

    assert(v1[1] == 20);
    assert(v2[1] == 30);
}

void test_move_constructor() {
    rtb::Vector<int> v1;

    v1.push_back(10);
    v1.push_back(20);

    rtb::Vector<int> v2(std::move(v1));

    assert(v2[0] == 10);
    assert(v2[1] == 20);
    assert(v2.size() == 2);
    assert(v2.capacity() == 2);
    assert(v2.data() != nullptr);

    assert(v1.data() == nullptr);
    assert(v1.size() == 0);
    assert(v1.capacity()  == 0);
    assert(v1.empty());
}

void test_copy_assignment_operator() {
    rtb::Vector<int> empty;
    rtb::Vector<int> empty_copy ;

    empty_copy = empty;

    assert(empty_copy.capacity() == 0);
    assert(empty_copy.size() == 0);
    assert(empty_copy.empty());

    rtb::Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);

    rtb::Vector<int> v2;
    v2 = v1;

    assert(v2.data() != v1.data());
    assert(v2.capacity() == v1.capacity());
    assert(v2.size() == v1.size());
    assert(v2[0] == v1[0]);
    assert(v2[1] == v1[1]);

    v2[1] = 30; 

    assert(v1[1] == 20);
    assert(v2[1] == 30);
}

void test_move_assignment_operator() {
    rtb::Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);

    rtb::Vector<int> v2;
    v2 = std::move(v1);

    assert(v2[0] == 10);
    assert(v2[1] == 20);
    assert(v2.size() == 2);
    assert(v2.capacity() == 2);
    assert(v2.data() != nullptr);

    assert(v1.data() == nullptr);
    assert(v1.size() == 0);
    assert(v1.capacity()  == 0);
    assert(v1.empty());
}

void test_size(){
    rtb::Vector<int> v;

    assert(v.size() == 0);

    v.push_back(10);
    assert(v.size() == 1);

    v.push_back(20);
    assert(v.size() == 2);

    v.insert(v.begin(), 5);
    assert(v.size() == 3);

    v.insert(v.begin() + 1, 7);
    assert(v.size() == 4);

    v.insert(v.end(), 100);
    assert(v.size() == 5);
}

void test_capacity(){
    rtb::Vector<int> v;

    assert(v.capacity() == 0);
    assert(v.capacity() >= v.size());

    v.push_back(10);
    assert(v.capacity() == 1);
    assert(v.capacity() >= v.size());

    v.push_back(20);
    assert(v.capacity() == 2);

    v.push_back(30);
    assert(v.capacity() == 4);

    v.push_back(40);
    assert(v.capacity() == 4);

    v.push_back(50);
    assert(v.capacity() == 8);

    assert(v.capacity() >= v.size());
}

void test_empty(){
    rtb::Vector<int> v;

    assert(v.empty());
    assert(v.size() == 0);

    v.push_back(10);

    assert(!v.empty());
    assert(v.size() == 1);
}

void test_data(){
    rtb::Vector<int> v;

    assert(v.data() == nullptr);
    
    v.push_back(10);

    assert(v.data() != nullptr);
    assert(v.data()[0] == 10);

    v.push_back(20);

    assert(v.data()[0] == 10);
    assert(v.data()[1] == 20);

    assert(v.data()[0] == v[0]);
    assert(v.data()[1] == v[1]);
    assert(&v[0] == v.data());
}

void test_data_const() {
    const rtb::Vector<int> v = {10, 20, 30};

    const int* ptr = v.data();

    assert(ptr != nullptr);
    assert(ptr[0] == 10);
    assert(ptr[1] == 20);
    assert(ptr[2] == 30);
}

void test_at(){
    rtb::Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    assert(v.at(0) == 10);
    assert(v.at(1) == 20);

    bool exceptionThrown = false;
    try {
        v.at(2);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
}

void test_at_const() {
    const rtb::Vector<int> v = {10, 20, 30};

    assert(v.at(0) == 10);
    assert(v.at(1) == 20);
    assert(v.at(2) == 30);

    bool thrown = false;

    try {
        v.at(3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown == true);
}

void test_operator_square_brackets(){
    rtb::Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    assert(v.operator[](0) == 10);
    assert(v.operator[](1) == 20);

    v[0] = 100;
    v[1] = 200;

    assert(v[0] == 100);
    assert(v[1] == 200);
}

void test_operator_square_brackets_const() {
    const rtb::Vector<int> v = {10, 20, 30};

    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
}

void test_front() {
    rtb::Vector<int> v;

    bool exceptionThrown = false;
    try {
        v.front();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    assert(v.front() == 10);

    v.front() = 99;

    assert(v[0] == 99);
}

void test_const_front() {
    const rtb::Vector<int> v = {10, 20, 30};

    assert(v.front() == 10);
}

void test_back(){
    rtb::Vector<int> v;

    bool exceptionThrown = false; 
    try {
        v.back();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    assert(v.back() == 30);
    
    v.back() = 99;

    assert(v[2] == 99);
}

void test_const_back() {
    const rtb::Vector<int> v = {10, 20, 30};

    assert(v.back() == 30);
}

void test_emplace_back() {
    rtb::Vector<int> v;

    v.emplace_back(10);
    v.emplace_back(20);

    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 20);

    size_t capacity_before = v.capacity();

    v.emplace_back(30);

    assert(v.capacity() > capacity_before);
    assert(v.size() == 3);
}

void test_push_back_copy(){
    rtb::Vector<int> v;

    v.push_back(10);
    v.push_back(20);

    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(!v.empty());
}

void test_push_back_move() {
    std::string str = "hello";

    rtb::Vector<std::string> v;

    v.push_back(std::move(str));

    assert(v.size() == 1);
    assert(v[0] == "hello");
    assert(str.empty());
}

void test_emplace() {
    rtb::Vector<std::string> v = {"10", "30"};

    v.emplace(v.begin() + 1, 2, 'x');

    assert(v.size() == 3);
    assert(v[0] == "10");
    assert(v[1] == "xx");
    assert(v[2] == "30");
}

void test_insert_copy(){
    rtb::Vector<int> v;

    v.insert(v.begin(), 5);
    v.insert(v.begin(), 10);
    v.insert(v.begin() + 1, 20);
    v.insert(v.begin() + 1, 15);
    v.insert(v.end(), 25);

    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 15);
    assert(v[2] == 20);
    assert(v[3] == 5);
    assert(v[4] == 25);
    assert(!v.empty());
}

void test_insert_move() {
    rtb::Vector<std::string> v = {"10", "30"};

    std::string str = "20";
    v.insert(v.begin() + 1, std::move(str));

    assert(v.size() == 3);
    assert(v[0] == "10");
    assert(v[1] == "20");
    assert(v[2] == "30");
}

void test_insert_count() {
    rtb::Vector<int> v = {10, 40};

    v.insert(v.begin() + 1, 2, 20);

    assert(v.size() == 4);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 20);
    assert(v[3] == 40);
}

void test_insert_range() {
    rtb::Vector<int> v = {10, 50};
    int arr[] = {20, 30, 40};

    v.insert(v.begin() + 1, arr, arr + 3);

    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
    assert(v[3] == 40);
    assert(v[4] == 50);
}

void test_insert_initializer_list() {
    rtb::Vector<int> v = {10, 50};

    v.insert(v.begin() + 1, {20, 30, 40});

    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
    assert(v[3] == 40);
    assert(v[4] == 50);
}

void test_pop_back() {
    rtb::Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    size_t capacity_before = v.capacity();
    size_t size_before = v.size();

    v.pop_back();

    assert(v.size() == size_before - 1);
    assert(v.capacity() == capacity_before);

    assert(v[0] == 10);
    assert(v[1] == 20);

    v.pop_back();
    v.pop_back();

    assert(v.size() == 0);
    assert(v.capacity() == capacity_before);
}

void test_erase_one() {
    rtb::Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    v.push_back(60);

    size_t capacity_before = v.capacity();
    size_t size_before = v.size();

    v.erase(0);
    assert(v.capacity() == capacity_before);
    assert(v.size() == size_before - 1);
    assert(v[0] == 20); 

    v.erase(2);
    assert(v.capacity() == capacity_before);
    assert(v.size() == size_before - 2);
    assert(v[2] == 50);

    v.erase(3);
    assert(v.capacity() == capacity_before);
    assert(v.size() == size_before - 3);
    assert(v[2] == 50);
}

void test_clear(){
    rtb::Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    size_t capacity_before = v.capacity();

    v.clear();

    assert(v.size() == 0);
    assert(v.capacity() == capacity_before);

    v.push_back(100);

    assert(v.size() == 1);
    assert(v[0] == 100);
} 

void test_reserve() {
    rtb::Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    size_t size_before = v.size();
    size_t capacity_before = v.capacity();

    v.reserve(10);

    assert(v.size() == size_before);
    assert(v.capacity() >= 10);
    assert(v[0] == 1);
    assert(v[1] == 2);

    size_t capacity_now = v.capacity();

    v.reserve(5);

    assert(v.capacity() == capacity_now);
    assert(v.size() == size_before);
}

void test_resize() {
    rtb::Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    size_t capacity_before_shrink = v.capacity();

    v.resize(2);

    assert(v.size() == 2);
    assert(v.capacity() == capacity_before_shrink);
    assert(v[0] == 10);
    assert(v[1] == 20);

    v.resize(5);

    assert(v.size() == 5);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 0);
    assert(v[3] == 0);
    assert(v[4] == 0);

    size_t size_before_same = v.size();
    size_t capacity_before_same = v.capacity();

    v.resize(5);

    assert(v.size() == size_before_same);
    assert(v.capacity() == capacity_before_same);
    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 0);
    assert(v[3] == 0);
    assert(v[4] == 0);

    v.resize(0);

    assert(v.size() == 0);
    assert(v.capacity() == capacity_before_same);

    v.resize(3);

    assert(v.size() == 3);
    assert(v[0] == 0);
    assert(v[1] == 0);
    assert(v[2] == 0);

    size_t capacity_before_grow = v.capacity();

    v.resize(100);

    assert(v.size() == 100);
    assert(v.capacity() >= 100);
    assert(v.capacity() > capacity_before_grow);
    assert(v[0] == 0);
}

void test_swap() {
    rtb::Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    rtb::Vector<int> b;
    b.push_back(10);
    b.push_back(20);

    size_t a_size = a.size();
    size_t b_size = b.size();

    size_t a_capacity = a.capacity();
    size_t b_capacity = b.capacity();

    a.swap(b);

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


int main() {
    test_begin();
    test_end();
    test_cbegin();
    test_cend();

    test_constructor();
    test_constructor_with_size();
    test_constructor_with_size_and_value();
    test_constructor_with_initializer_list();
    test_constructor_with_range();

    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment_operator();
    test_move_assignment_operator();

    test_size();
    test_capacity();
    test_empty();
    test_data();
    test_data_const();

    test_at();
    test_at_const();
    test_operator_square_brackets();
    test_operator_square_brackets_const();
    test_front();
    test_back();
    test_const_front();
    test_const_back();

    test_emplace_back();
    test_push_back_copy();
    test_push_back_move();

    test_emplace();
    test_insert_copy();
    test_insert_move();
    test_insert_count();
    test_insert_range();
    test_insert_initializer_list();

    test_pop_back();
    test_erase_one();
    test_clear();

    test_reserve();
    test_resize();

    test_swap();

    std::cout << "All manual unit tests passed!\n";
    return 0;
}
