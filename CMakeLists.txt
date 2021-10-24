cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  fintamath
  LANGUAGES CXX
  VERSION 1.0)

option(BUILD_APP "Enable Test Builds" ON)
option(BUILD_TESTS "Enable Test Builds" ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)

if(BUILD_TESTS)
  include(GoogleTest)
  enable_testing()
endif()

add_subdirectory(third_party)
add_subdirectory(src)
