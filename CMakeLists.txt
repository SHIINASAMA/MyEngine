cmake_minimum_required(VERSION 3.0)
project(MyEngine)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "-fPIC")
set(CMAKE_CXX_FLAGS "-fPIC")
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

include_directories(src)
include_directories(thirdparty/yaml-cpp/include)
include_directories(thirdparty/sqlite)

include(Build.cmake)