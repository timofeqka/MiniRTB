# MiniRTB JSON Demo

## Description
This project demonstrates how to work with JSON in C++ using the nlohmann/json library.

## Features
- JSON structure for campaigns
- Serialization and deserialization
- Demo program for reading, modifying, and saving JSON
- Custom `Vector` container implementation
- Manual unit tests for core data structures
- CMake build configuration

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