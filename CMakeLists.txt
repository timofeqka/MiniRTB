cmake_minimum_required(VERSION 3.16)

project(MiniRTB LANGUAGES CXX)

#add_subdirectory(tools/json_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vector_tests
    tests/test_vector_manual.cpp
)

target_include_directories(vector_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/common/include
)