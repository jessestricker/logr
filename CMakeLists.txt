cmake_minimum_required(VERSION 3.10)
project(log
    VERSION 0.1.0
    LANGUAGES CXX)

# library
add_library(log
    src/log.cpp)
target_compile_features(log PUBLIC cxx_std_17)
target_include_directories(log INTERFACE include)
target_include_directories(log PRIVATE include/log)
target_link_libraries(log PUBLIC meta)

# dependencies
add_subdirectory(lib/meta)
