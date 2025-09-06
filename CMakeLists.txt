cmake_minimum_required(VERSION 3.5...3.28)

project(
  fintamath
  LANGUAGES CXX
  VERSION 0.9.0)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/CCache.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(PROJECT_EXPORT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/fintamath/core/FintamathExport.hpp)
string(TOUPPER ${PROJECT_NAME}_STATIC_DEFINE PROJECT_STATIC_DEFINE)

option(${PROJECT_NAME}_build_shared "Build shared" OFF)
option(${PROJECT_NAME}_build_tests "Build tests" OFF)

if(${PROJECT_NAME}_build_shared)
  option(${PROJECT_NAME}_build_benchmarks "Build benchmarks" OFF)
endif()

add_subdirectory(thirdparty)

find_package(MPFR REQUIRED)

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
  add_library(${PROJECT_NAME} OBJECT ${SOURCES})
  target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_STATIC_DEFINE})
endif()

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC include
  PRIVATE src)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC fmt::fmt-header-only
         MPFR
         Boost::multiprecision
         Boost::math)

include(cmake/CompilerWarnings.cmake)
include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/ClangFormat.cmake)

include(GenerateExportHeader)
generate_export_header(
  ${PROJECT_NAME}
  EXPORT_FILE_NAME
  "${PROJECT_EXPORT_FILE}"
  STATIC_DEFINE
  "${PROJECT_STATIC_DEFINE}")

if(${PROJECT_NAME}_build_tests)
  enable_testing()
  add_subdirectory(tests)
endif()

if(${PROJECT_NAME}_build_benchmarks)
  add_subdirectory(benchmarks)
endif()

unset(PROJECT_EXPORT_FILE)
unset(PROJECT_STATIC_DEFINE)
