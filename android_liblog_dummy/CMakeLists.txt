cmake_minimum_required(VERSION 3.4.1)

# Define the library
add_library(log STATIC log.cpp)

# Specify the include directories (if any)
target_include_directories(log PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Specify the C++ standard (optional)
set_target_properties(log PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON)
