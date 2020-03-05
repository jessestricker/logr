cmake_minimum_required(VERSION 3.10)
project(logr
    VERSION 0.1.0
    LANGUAGES CXX)

# library
add_library(logr
    src/logger.cpp
    src/record.cpp)
target_compile_features(logr PUBLIC cxx_std_17)
target_include_directories(logr PUBLIC include)
target_include_directories(logr PRIVATE include/logr)
target_link_libraries(logr PUBLIC meta)

# dependencies
add_subdirectory(lib/meta)
