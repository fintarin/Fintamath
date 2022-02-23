cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  fintamath
  LANGUAGES CXX
  VERSION 0.1)

option(BUILD_TESTS "Enable Test Builds" ON)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/Cache.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)

add_subdirectory(third_party)

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp"
  "src/*.hpp"
  "include/*.hpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC include
  PRIVATE src)

if(BUILD_TESTS)
  include(GoogleTest)
  enable_testing()
  add_subdirectory(tests)
endif()
