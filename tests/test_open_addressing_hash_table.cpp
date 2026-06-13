#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <string>
#include "minirtb/storage/open_addressing_hash_table.hpp"

void test_constructor() {
    rtb::FlatHashTable<int, int> table;

    assert(table.size() == 0);
    assert(table.empty() == true);
    assert(table.bucket_count() == 16);
    assert(table.load_factor() == 0.0f);
    assert(table.max_load_factor() == 0.7f);
    assert(table.contains(10) == false);
    assert(table.find(10) == nullptr);

    bool exception_thrown = false;
    try {
        table.at(10);
    } catch (const std::out_of_range&) {
        exception_thrown = true;
    }

    assert(exception_thrown == true); 

    table.insert(1, 100);

    assert(table.size() == 1);
    assert(table.empty() == false);
    assert(table.contains(1) == true);
    assert(table.find(1) != nullptr);
    assert(*table.find(1) == 100);
    assert(table.at(1) == 100);
}

void test_constructor_with_bucket_count() {
    rtb::FlatHashTable<int, int> table(10);

    assert(table.size() == 0);
    assert(table.empty() == true);
    assert(table.load_factor() == 0.0f);
    assert(table.bucket_count() == 10);

    table.insert(1, 100);

    assert(table.size() == 1);
    assert(table.empty() == false);
    assert(table.contains(1) == true);

    int* value = table.find(1);
    assert(value != nullptr);
    assert(*value == 100);
    assert(table.at(1) == 100);
    assert(table.load_factor() == 0.1f);

    rtb::FlatHashTable<int, int> zero_table(0);

    assert(zero_table.size() == 0);
    assert(zero_table.empty() == true);
    assert(zero_table.load_factor() == 0.0f);
    assert(zero_table.bucket_count() == 16);

    zero_table.insert(5, 500);

    assert(zero_table.size() == 1);
    assert(zero_table.empty() == false);
    assert(zero_table.contains(5) == true);

    int* zero_value = zero_table.find(5);
    assert(zero_value != nullptr);
    assert(*zero_value == 500);

    assert(zero_table.at(5) == 500);
}

void test_rule_of_five_basic() {
    //Destructor for empty table
    {
        rtb::FlatHashTable<int, int> table;
        assert(table.empty() == true);
        assert(table.size() == 0);
    }
    //Destructor for table with elements
    {
        rtb::FlatHashTable<int, int> table;

        table.insert(1, 100);
        table.insert(2, 200);

        assert(table.size() == 2);
        assert(table.at(1) == 100);
        assert(table.at(2) == 200);
    }
    //Copy constructor
    {
        rtb::FlatHashTable<int, int> original;

        original.insert(1, 100);
        original.insert(2, 200);

        rtb::FlatHashTable<int, int> copy(original);

        assert(copy.size() == 2);
        assert(copy.at(1) == 100);
        assert(copy.at(2) == 200);

        copy.insert_or_assign(1, 999);

        assert(copy.at(1) == 999);
        assert(original.at(1) == 100);
    }
    //Copy assignment
    {
        rtb::FlatHashTable<int, int> original;

        original.insert(1, 100);
        original.insert(2, 200);

        rtb::FlatHashTable<int, int> copy;

        copy.insert(9, 900);
        copy = original;

        assert(copy.size() == 2);
        assert(copy.contains(9) == false);
        assert(copy.at(1) == 100);
        assert(copy.at(2) == 200);

        copy.insert_or_assign(1, 999);

        assert(copy.at(1) == 999);
        assert(original.at(1) == 100);
    }
    //Copy self-assignment
    {
        rtb::FlatHashTable<int, int> table;

        table.insert(1, 100);
        table.insert(2, 200);

        table = table;

        assert(table.size() == 2);
        assert(table.at(1) == 100);
        assert(table.at(2) == 200);
    }
    //Move constructor
    {
        rtb::FlatHashTable<int, int> original;

        original.insert(1, 100);
        original.insert(2, 200);

        rtb::FlatHashTable<int, int> moved(std::move(original));

        assert(moved.size() == 2);
        assert(moved.at(1) == 100);
        assert(moved.at(2) == 200);

        original.clear();
        assert(original.empty() == true);
    }
    //Move assignment
    {
        rtb::FlatHashTable<int, int> original;

        original.insert(1, 100);
        original.insert(2, 200);

        rtb::FlatHashTable<int, int> moved;

        moved.insert(9, 900);
        moved = std::move(original);

        assert(moved.size() == 2);
        assert(moved.contains(9) == false);
        assert(moved.at(1) == 100);
        assert(moved.at(2) == 200);

        original.clear();
        assert(original.empty() == true);
    }
    //Move self-assignment
    {
        rtb::FlatHashTable<int, int> table;

        table.insert(1, 100);
        table.insert(2, 200);

        table = std::move(table);

        assert(table.size() == 2);
        assert(table.at(1) == 100);
        assert(table.at(2) == 200);
    }
    //Clear before destructor
    {
        rtb::FlatHashTable<int, int> table;

        table.insert(1, 100);
        table.insert(2, 200);

        table.clear();

        assert(table.size() == 0);
        assert(table.empty() == true);
        assert(table.contains(1) == false);
        assert(table.contains(2) == false);
    }
}

void test_size() {
    rtb::FlatHashTable<int, int> table;

    assert(table.size() == 0);

    table.emplace(1, 100);
    assert(table.size() == 1);

    table.insert(2, 200);
    assert(table.size() == 2);

    table.insert_or_assign(3, 300);
    assert(table.size() == 3);
    table.insert_or_assign(3, 999);
    assert(table.size() == 3);
    assert(table.at(3) == 999);

    table.insert(2, 222);
    assert(table.size() == 3);
    assert(table.at(2) == 200);

    table.emplace(1, 111);
    assert(table.size() == 3);
    assert(table.at(1) == 100);

    table.erase(1);
    assert(table.size() == 2);
    assert(table.contains(1) == false);
    table.erase(999);
    assert(table.size() == 2);

    table.rehash(64);
    assert(table.size() == 2);
    assert(table.at(2) == 200);
    assert(table.at(3) == 999);

    table.reserve(100);
    assert(table.size() == 2);
    assert(table.at(2) == 200);
    assert(table.at(3) == 999);

    table.clear();
    assert(table.size() == 0);
    assert(table.empty() == true);
}

void test_bucket_count() {
    rtb::FlatHashTable<int, int> table(3);

    assert(table.bucket_count() == 3);

    table.insert(1, 100);
    assert(table.bucket_count() == 3);
    table.insert(2, 200);
    assert(table.bucket_count() == 3);

    table.erase(1);
    assert(table.bucket_count() == 3);

    table.rehash(10);
    assert(table.bucket_count() == 10);

    table.clear();
    assert(table.bucket_count() == 10);
}

void test_empty() {
    rtb::FlatHashTable<int, int> table;
    assert(table.empty() == true);
    assert(table.size() == 0);

    table.insert(1, 100);
    assert(table.empty() == false);
    assert(table.size() == 1);

    table.erase(1);
    assert(table.empty() == true);
    assert(table.size() == 0);

    table.insert(2, 200);
    table.insert(3, 300);
    assert(table.empty() == false);
    assert(table.size() == 2);
    table.clear();
    assert(table.empty() == true);
    assert(table.size() == 0);

    rtb::FlatHashTable<int, int> original;
    original.insert(10, 1000);
    original.insert(20, 2000);

    rtb::FlatHashTable<int, int> copy(original);
    assert(original.empty() == false);
    assert(copy.empty() == false);
    assert(original.size() == 2);
    assert(copy.size() == 2);


    rtb::FlatHashTable<int, int> empty_original;
    rtb::FlatHashTable<int, int> empty_copy(empty_original);
    assert(empty_original.empty() == true);
    assert(empty_copy.empty() == true);
    assert(empty_original.size() == 0);
    assert(empty_copy.size() == 0);


    rtb::FlatHashTable<int, int> moved(std::move(original));
    assert(moved.empty() == false);
    assert(moved.size() == 2);
    assert(moved.at(10) == 1000);
    assert(moved.at(20) == 2000);


    original.clear();
    assert(original.empty() == true);
    assert(original.size() == 0);


    rtb::FlatHashTable<int, int> moved_empty(std::move(empty_original));
    assert(moved_empty.empty() == true);
    assert(moved_empty.size() == 0);
}

void test_load_factor() {
    rtb::FlatHashTable<int, int> table(10);
    assert(table.load_factor() == 0.0f);

    table.insert(1, 100);
    assert(table.load_factor() > 0.0f);
    assert(std::fabs(table.load_factor() - 0.1f) < 0.0001f);

    table.insert(2, 200);
    assert(table.size() == 2);
    assert(std::fabs(table.load_factor() - 0.2f) < 0.0001f);

    float before_erase = table.load_factor();
    table.erase(1);

    float after_erase = table.load_factor();
    assert(table.size() == 1);
    assert(after_erase < before_erase);
    assert(std::fabs(table.load_factor() - 0.1f) < 0.0001f);

    float before_reserve = table.load_factor();
    table.reserve(100);

    float after_reserve = table.load_factor();
    assert(table.size() == 1);
    assert(std::fabs(after_reserve - before_reserve) < 0.0001f);

    table.clear();
    assert(table.size() == 0);
    assert(table.empty() == true);
    assert(table.load_factor() == 0.0f);
}

void test_max_load_factor() {
    rtb::FlatHashTable<int, int> table;
    assert(std::fabs(table.max_load_factor() - 0.7f) < 0.0001f);

    table.set_max_load_factor(0.5f);
    assert(std::fabs(table.max_load_factor() - 0.5f) < 0.0001f);
}

void test_contains() {
    rtb::FlatHashTable<int, int> table;
    assert(table.contains(1) == false);

    table.insert(1, 100);
    assert(table.contains(1) == true);

    assert(table.contains(2) == false);

    table.emplace(2, 200);
    assert(table.contains(2) == true);

    table.erase(1);
    assert(table.contains(1) == false);
    assert(table.contains(2) == true);

    table.clear();
    assert(table.contains(2) == false);
}

void test_find() {
    rtb::FlatHashTable<int, int> table;

    assert(table.find(1) == nullptr);

    table.insert(1, 100);

    int* value = table.find(1);
    assert(value != nullptr);
    assert(*value == 100);

    assert(table.find(2) == nullptr);

    table.emplace(2, 200);

    int* second_value = table.find(2);
    assert(second_value != nullptr);
    assert(*second_value == 200);

    table.erase(1);
    assert(table.find(1) == nullptr);
    assert(table.find(2) != nullptr);

    table.clear();
    assert(table.find(2) == nullptr);
}

void test_const_find() {
    rtb::FlatHashTable<int, int> table;

    table.insert(1, 100);
    table.insert(2, 200);

    const rtb::FlatHashTable<int, int>& const_table = table;
    const int* value = const_table.find(1);
    assert(value != nullptr);
    assert(*value == 100);

    const int* second_value = const_table.find(2);
    assert(second_value != nullptr);
    assert(*second_value == 200);

    assert(const_table.find(999) == nullptr);

    table.erase(1);
    assert(const_table.find(1) == nullptr);
    assert(const_table.find(2) != nullptr);

    table.clear();
    assert(const_table.find(2) == nullptr);
}

void test_at() {
    rtb::FlatHashTable<int, int> table;

    bool thrown = false;
    try {
        table.at(1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown == true);

    table.insert(1, 100);
    assert(table.at(1) == 100);

    table.at(1) = 999;
    assert(table.at(1) == 999);

    table.emplace(2, 200);
    assert(table.at(2) == 200);

    table.erase(1);
    thrown = false;
    try {
        table.at(1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown == true);
    table.clear();
    thrown = false;
    try {
        table.at(2);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown == true);
}

void test_const_at() {
    rtb::FlatHashTable<int, int> table;
    table.insert(1, 100);
    table.insert(2, 200);

    const rtb::FlatHashTable<int, int>& const_table = table;
    assert(const_table.at(1) == 100);
    assert(const_table.at(2) == 200);

    bool thrown = false;
    try {
        const_table.at(999);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown == true);

    table.erase(1);
    thrown = false;
    try {
        const_table.at(1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown == true);

    table.clear();
    thrown = false;
    try {
        const_table.at(2);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown == true);
}

void test_emplace() {
    rtb::FlatHashTable<int, int> table;
    table.emplace(1, 100);
    assert(table.size() == 1);
    assert(table.contains(1) == true);
    assert(table.at(1) == 100);

    table.emplace(1, 999);
    assert(table.size() == 1);
    assert(table.at(1) == 100);

    table.emplace(2, 200);
    assert(table.size() == 2);
    assert(table.contains(2) == true);
    assert(table.at(2) == 200);
}

void test_insert() {
    rtb::FlatHashTable<int, int> table;
    int value = 100;
    table.insert(1, value);

    assert(table.size() == 1);
    assert(table.at(1) == 100);

    int new_value = 999;
    table.insert(1, new_value);
    assert(table.size() == 1);
    assert(table.at(1) == 100);
}

void test_const_insert() {
    rtb::FlatHashTable<int, int> table;
    table.insert(1, 100);
    assert(table.size() == 1);
    assert(table.at(1) == 100);

    table.insert(1, 999);
    assert(table.size() == 1);
    assert(table.at(1) == 100);
}

void test_insert_or_assign() {
    rtb::FlatHashTable<int, int> table;
    int value = 100;
    table.insert_or_assign(1, value);
    assert(table.size() == 1);
    assert(table.at(1) == 100);

    int new_value = 999;
    table.insert_or_assign(1, new_value);
    assert(table.size() == 1);
    assert(table.at(1) == 999);
}

void test_const_insert_or_assign() {
    rtb::FlatHashTable<int, int> table;
    table.insert_or_assign(1, 100);

    assert(table.size() == 1);
    assert(table.at(1) == 100);

    table.insert_or_assign(1, 999);
    assert(table.size() == 1);
    assert(table.at(1) == 999);
}

void test_erase() {
    rtb::FlatHashTable<int, int> table;
    table.erase(1);
    assert(table.size() == 0);
    assert(table.empty() == true);

    table.insert(1, 100);
    table.insert(2, 200);
    assert(table.size() == 2);

    table.erase(1);

    assert(table.size() == 1);
    assert(table.contains(1) == false);
    assert(table.find(1) == nullptr);
    assert(table.contains(2) == true);
    assert(table.at(2) == 200);

    table.erase(999);
    assert(table.size() == 1);
    assert(table.contains(2) == true);

    table.erase(2);
    assert(table.size() == 0);
    assert(table.empty() == true);
    assert(table.contains(2) == false);
}

void test_clear() {
    rtb::FlatHashTable<int, int> table;
    table.clear();

    assert(table.size() == 0);
    assert(table.empty() == true);

    table.insert(1, 100);
    table.insert(2, 200);
    assert(table.size() == 2);
    assert(table.empty() == false);

    table.clear();
    assert(table.size() == 0);
    assert(table.empty() == true);
    assert(table.contains(1) == false);
    assert(table.contains(2) == false);
    assert(table.find(1) == nullptr);

    table.clear();
    assert(table.size() == 0);
    assert(table.empty() == true);
}

void test_set_max_load_factor() {
    rtb::FlatHashTable<int, int> table;

    table.set_max_load_factor(0.5f);
    assert(std::fabs(table.max_load_factor() - 0.5f) < 0.0001f);

    bool thrown = false;

    try {
        table.set_max_load_factor(0.0f);
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;

    try {
        table.set_max_load_factor(-1.0f);
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;

    try {
        table.set_max_load_factor(1.5f);
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    assert(thrown);
}

void test_reserve() {
    rtb::FlatHashTable<int, int> table;

    table.reserve(100);
    assert(table.size() == 0);
    assert(table.empty() == true);

    table.insert(1, 100);
    table.insert(2, 200);
    assert(table.size() == 2);
    assert(table.at(1) == 100);
    assert(table.at(2) == 200);

    table.reserve(1000);
    assert(table.size() == 2);
    assert(table.contains(1) == true);
    assert(table.contains(2) == true);
    assert(table.at(1) == 100);
    assert(table.at(2) == 200);

    table.reserve(1);
    assert(table.size() == 2);
    assert(table.at(1) == 100);
    assert(table.at(2) == 200);
}

void test_resize() {
    rtb::FlatHashTable<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);

    size_t old_bucket_count = table.bucket_count();

    table.resize(old_bucket_count * 2);

    assert(table.bucket_count() == old_bucket_count * 2);
    assert(table.size() == 2);
    assert(table.at(1) == 10);
    assert(table.at(2) == 20);

    table.resize(old_bucket_count);

    assert(table.bucket_count() == old_bucket_count * 2);
    assert(table.size() == 2);
}

void test_rehash() {
    rtb::FlatHashTable<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    size_t old_bucket_count = table.bucket_count();

    table.rehash(old_bucket_count * 2);

    assert(table.size() == 3);
    assert(table.bucket_count() == old_bucket_count * 2);

    assert(table.at(1) == 10);
    assert(table.at(2) == 20);
    assert(table.at(3) == 30);
}

void test_swap() {
    rtb::FlatHashTable<int, int> first;
    rtb::FlatHashTable<int, int> second;

    first.insert(1, 100);
    first.insert(2, 200);

    second.insert(10, 1000);

    first.swap(second);

    assert(first.size() == 1);
    assert(first.contains(10) == true);
    assert(first.at(10) == 1000);
    assert(first.contains(1) == false);
    assert(first.contains(2) == false);

    assert(second.size() == 2);
    assert(second.contains(1) == true);
    assert(second.contains(2) == true);
    assert(second.at(1) == 100);
    assert(second.at(2) == 200);
    assert(second.contains(10) == false);


    rtb::FlatHashTable<int, int> empty;
    empty.swap(second);
    assert(empty.size() == 2);
    assert(empty.at(1) == 100);
    assert(empty.at(2) == 200);

    assert(second.size() == 0);
    assert(second.empty() == true);

    first.swap(first);
    assert(first.size() == 1);
    assert(first.at(10) == 1000);
}

int main() {
    test_constructor();
    test_constructor_with_bucket_count();
    test_rule_of_five_basic();

    test_size();
    test_bucket_count();
    test_empty();
    test_load_factor();
    test_max_load_factor();

    test_contains();
    test_find();
    test_const_find();
    test_at();
    test_const_at();

    test_emplace();
    test_insert();
    test_const_insert();

    test_insert_or_assign();
    test_const_insert_or_assign();

    test_erase();

    test_clear();

    test_set_max_load_factor();

    test_reserve();
    test_resize();
    test_rehash();

    test_swap();

    std::cout << "All manual unit tests passed!\n";
    return 0;
}