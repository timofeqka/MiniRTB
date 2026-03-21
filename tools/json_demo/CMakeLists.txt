add_executable(json_demo
    src/main.cpp
)

target_include_directories(json_demo PRIVATE
    ${PROJECT_SOURCE_DIR}/src/domain/include
    ${PROJECT_SOURCE_DIR}/third_party/nlohmann_json/include
)

target_compile_features(json_demo PRIVATE cxx_std_17)