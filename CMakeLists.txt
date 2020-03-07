cmake_minimum_required(VERSION 3.10)
project(logr
    VERSION 0.2.0
    LANGUAGES CXX)

# helper functions
function(logr_add_example name)
  add_executable(logr_example_${name} examples/${name}.cpp)
  target_link_libraries(logr_example_${name} PRIVATE logr Threads::Threads)
endfunction()

# library
add_library(logr
    src/default.cpp
    src/logger.cpp
    src/record.cpp)
target_compile_features(logr PUBLIC cxx_std_17)
target_include_directories(logr PUBLIC include)
target_include_directories(logr PRIVATE include/logr)
target_link_libraries(logr PUBLIC meta)

# examples
logr_add_example(builder)
logr_add_example(global)
logr_add_example(simple)

# dependencies
add_subdirectory(lib/meta)
find_package(Threads REQUIRED)
