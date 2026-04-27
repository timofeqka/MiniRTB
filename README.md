# MiniRTB

## Description
This project currently focuses on a custom implementation of a dynamic array (`Vector`) and manual unit tests for its core behavior.
The repository also contains JSON demo files for campaign data, but the root CMake build is set up to build the vector test executable.

---

## Features
- Custom `Vector` container implementation
- Copy and move constructors
- Copy and move assignment operators
- Element insertion and erase behavior
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
- `insert()` - insert element at position
- `operator[]` - direct access (no bounds check)
- `at()` - safe access (throws exception)
- `size() / capacity() / empty()`
- `data()` - pointer to underlying storage
- copy constructor
- move constructor
- copy assignment operator
- move assignment operator
- `errase()` - remove value by its position

## Testing
Manual unit tests cover:
- constructor behavior
- size and capacity growth
- memory layout (contiguous storage)
- element access (`operator[]`, `at()`)
- insertion logic and shifting
- copy constructor behavior
- move constructor behavior
- copy assignment behavior
- move assignment behavior
- erase behavior
- exception handling
