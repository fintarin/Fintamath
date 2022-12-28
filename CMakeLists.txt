cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  fintamath
  LANGUAGES CXX C
  VERSION 0.3)

include(cmake/PreventInSourceBuilds.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Coverage.cmake)
include(cmake/Sanitizers.cmake)

option(${PROJECT_NAME}_build_shared "Build shared" OFF)
option(${PROJECT_NAME}_build_tests "Build tests" OFF)

add_subdirectory(thirdparty)
add_subdirectory(src)

include(cmake/CompilerWarnings.cmake)

if(${PROJECT_NAME}_build_tests)
  enable_testing()
  include(cmake/FetchGtest.cmake)
  add_subdirectory(tests)
endif()
