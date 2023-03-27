cmake_minimum_required(VERSION 3.22)
project(sim)
set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/src)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        main.cpp
        )

file(GLOB all_SRCS_T
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        tests/tests.cpp
        )

add_executable(sim ${all_SRCS})
add_executable(test ${all_SRCS_T})
