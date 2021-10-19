cmake_minimum_required(VERSION 3.15.0)
project(algebra-calculator VERSION 1.0)

file(
  GLOB_RECURSE
  SRC_LIST
  "src/*.cpp"
  "src/*.hpp")

add_executable(${PROJECT_NAME} ${SRC_LIST})
