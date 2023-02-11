cmake_minimum_required(VERSION 3.10)

project(05_homework CXX)

add_executable(05_homework    
    source/main.cpp
)

target_include_directories(05_homework PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(05_homework PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(05_homework PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

target_compile_features(05_homework PUBLIC cxx_std_17)
