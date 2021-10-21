cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
  fintamath
  LANGUAGES CXX
  VERSION 1.0)

option(ENABLE_TESTING "Enable Test Builds" ON)

add_subdirectory(third_party)
add_subdirectory(src)

if(ENABLE_TESTING)
  include(GoogleTest)
  enable_testing()
  add_subdirectory(tests)
endif()
