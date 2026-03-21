# MiniRTB JSON Demo

## Description
This project demonstrates how to work with JSON in C++ using the nlohmann/json library.

## Features
- JSON structure for campaigns
- Serialization and deserialization
- Demo program for reading, modifying, and saving JSON
- CMake build configuration

## Project Structure
- `configs/campaigns/campaigns.json` - stores campaign data
- `src/domain/include/minirtb/domain/campaign.hpp` - campaign model and JSON conversion
- `tools/json_demo/src/main.cpp` - demo application
- `CMakeLists.txt` - root CMake configuration
- `tools/json_demo/CMakeLists.txt` - demo target build configuration

## Build
```bash
cmake -S . -B build
cmake --build build