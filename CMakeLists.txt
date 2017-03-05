cmake_minimum_required (VERSION 3.5)
project(magnus)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cxxblas/cmake")
include(CXXBLAS)

add_subdirectory(src)
