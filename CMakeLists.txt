cmake_minimum_required(VERSION 3.5...3.22)

project(
  fintamath
  LANGUAGES CXX
  VERSION 0.7.0)

include(cmake/PreventInSourceBuilds.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option(${PROJECT_NAME}_build_shared "Build shared" OFF)
option(${PROJECT_NAME}_build_tests "Build tests" OFF)

add_subdirectory(thirdparty)

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "include/*.hpp"
  "src/*.hpp"
  "src/*.cpp")

if(${PROJECT_NAME}_build_shared)
  add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
  add_library(${PROJECT_NAME} ${SOURCES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC include
  PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::multiprecision Boost::math)

include(cmake/CompilerWarnings.cmake)
include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/ClangFormat.cmake)

if(${PROJECT_NAME}_build_tests)
  enable_testing()
  include(cmake/FetchGtest.cmake)
  add_subdirectory(tests)
endif()
