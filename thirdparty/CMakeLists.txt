include(../cmake/SuppressCompilerWarnings.cmake)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/mpfr-gmp-prebuilt
    PARENT_SCOPE)

add_subdirectory(fmt)
suppress_compiler_warnings(fmt-header-only)

add_subdirectory(boost-multiprecision)
suppress_compiler_warnings(boost_multiprecision)

add_subdirectory(boost-math)
suppress_compiler_warnings(boost_math)

if(${PROJECT_NAME}_build_tests)
  add_subdirectory(googletest)
endif()

if(${PROJECT_NAME}_build_benchmarks)
  set(BENCHMARK_ENABLE_TESTING OFF)
  add_subdirectory(benchmark)
endif()
