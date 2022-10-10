cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  fintamath
  LANGUAGES CXX
  VERSION 0.3)

include(cmake/PreventInSourceBuilds.cmake)

option(${PROJECT_NAME}_build_tests "Build tests" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

include(cmake/FetchDependencies.cmake)
include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)

add_subdirectory(src)

if(${PROJECT_NAME}_build_tests)
  enable_testing()
  add_subdirectory(tests)
endif()

include(cmake/CompilerWarnings.cmake)
