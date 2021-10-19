cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Fintamath LANGUAGES CXX)

option(ENABLE_TESTING "Enable Test Builds" ON)

add_subdirectory(third_party)
add_subdirectory(src)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
