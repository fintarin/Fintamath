cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  fintamath
  LANGUAGES CXX
  VERSION 0.1)

option(${PROJECT_NAME}_enable_tests "Enable Test Builds" OFF)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/Cache.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/FetchDependencies.cmake)
include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)

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

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

if(${PROJECT_NAME}_enable_tests)
  include(GoogleTest)
  enable_testing()
  add_subdirectory(tests)
endif()
