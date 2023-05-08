cmake_minimum_required(VERSION 3.10)

project(project_work CXX)

add_executable(project_work
        source/main.cpp
        )

target_include_directories(project_work PRIVATE
        include
        ../argv_parser/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(project_work PRIVATE
            -g
            -Wall
            -Wextra
            -Werror
            -pedantic
            )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(project_work PRIVATE
            /EHsc
            /W4
            /WX
            )
endif()

target_link_libraries(project_work argv_parser_library)

target_compile_features(project_work PUBLIC cxx_std_17)
