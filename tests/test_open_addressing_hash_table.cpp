#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <string>
#include "minirtb/storage/open_addressing_hash_table.hpp"

void test_rehash() {
    rtb::FlatHashTable<int, int> table(4);

    table.insert(1, 100);
    table.insert(5, 500);
    table.insert(9, 900);

    table.rehash(16);

    assert(table.at(1) == 100);
    assert(table.at(5) == 500);
    assert(table.at(9) == 900);
    assert(table.size() == 3);
}

int main() {
    test_rehash();

    std::cout << "All manual unit tests passed!\n";
    return 0;
}