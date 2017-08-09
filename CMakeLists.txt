cmake_minimum_required(VERSION 3.8)
project(rocksred)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILE "g++")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES main.cpp)
add_executable(rocksred ${SOURCE_FILES})

target_link_libraries(rocksred librocksdb.dylib)
