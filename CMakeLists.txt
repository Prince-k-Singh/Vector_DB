cmake_minimum_required(VERSION 3.16)

project(Vector_DB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_vector_record
    tests/test_vector_record.cpp
)

add_executable(test_vector_store
    tests/test_vector_store.cpp
)