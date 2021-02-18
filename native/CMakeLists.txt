cmake_minimum_required(VERSION 3.0.0)
project(algebra-calculator VERSION 0.1.0)

file(GLOB_RECURSE TARGET_SRC
    "./calculator/*.cpp" "./calculator/*.hpp"
    "./numbers/*.cpp" "./numbers/*.hpp"
    "./operators/*.cpp" "./operators/*.hpp"
)

add_executable(algebra-calculator Main.cpp ${TARGET_SRC})

