# MiniRTB

## Description
This project currently focuses on a custom implementation of a dynamic array (`Vector`) and manual unit tests for its core behavior.
The repository also contains JSON demo files for campaign data, but the root CMake build is set up to build the vector test executable.

---

## Features
- Custom `Vector` container implementation
- Copy and move constructors
- Copy and move assignment operators
- Iterator-style access with raw pointer iterators
- Checked and unchecked element access
- Element insertion and erase behavior
- Capacity management with automatic growth and `reserve()`
- Resize, clear, pop, swap, front, back, and emplace operations
- Manual unit tests for core data structures
- CMake build configuration
- JSON campaign demo files kept in the repository

## Project Structure
- `configs/campaigns/campaigns.json` - stores campaign data
- `src/common/include/minirtb/campaign.hpp` - campaign model and JSON conversion
- `src/common/include/minirtb/storage/vector.hpp` - vector container implementation
- `tests/test_vector_manual.cpp` - tests vector container
- `tools/json_demo/src/main.cpp` - demo application
- `CMakeLists.txt` - root CMake configuration
- `tools/json_demo/CMakeLists.txt` - demo target build configuration

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Run Manual Unit Tests
```bash
.\build\Debug\vector_tests.exe
```

Expected output:
```text
All manual unit tests passed!
```

## Custom Vector
This project includes a simplified implementation of a dynamic array similar to `std::vector`.

## Supported Operations
- `pushBack()` - add element to the end
- `emplace_back()` - construct an element at the end
- `insert()` - insert element at position
- `errase()` - remove value by its position
- `pop_back()` - remove the last element
- `clear()` - remove all elements while keeping capacity
- `resize()` - change the number of stored elements
- `reserve()` - grow storage capacity without changing size
- `swap()` - exchange contents with another vector
- `operator[]` - direct access (no bounds check)
- `at()` - safe access (throws exception)
- `front() / back()` - access first and last elements
- `begin() / end() / cbegin() / cend()` - iterator access
- `size() / capacity() / empty()`
- `data()` - pointer to underlying storage
- copy constructor
- move constructor
- copy assignment operator
- move assignment operator

Not currently implemented:
- initializer-list constructor
- count-and-value constructor

## Testing
Manual unit tests cover:
- constructor behavior
- size and capacity growth
- memory layout (contiguous storage)
- element access (`operator[]`, `at()`)
- front and back access, including empty-vector exceptions
- iterator basics (`begin()` and `end()`)
- insertion logic and shifting
- copy constructor behavior
- move constructor behavior
- copy assignment behavior
- move assignment behavior
- erase behavior
- emplace, clear, resize, reserve, pop, and swap behavior
- exception handling
