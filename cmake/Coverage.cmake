# Enable coverage

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(${PROJECT_NAME}_enable_coverage "Enable coverage reporting for gcc/clang" OFF)
  if(${PROJECT_NAME}_enable_coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping -O0")

    add_custom_target(
      ${PROJECT_NAME}_coverage
      COMMAND ./bin/fintamath_tests
      COMMAND llvm-profdata merge -o merged.profdata *.profraw
      COMMAND llvm-cov show --show-branches=count --ignore-filename-regex='tests|build|thirdparty' --instr-profile
              merged.profdata bin/fintamath_tests > coverage.txt
      COMMAND llvm-cov export --ignore-filename-regex='tests|build|thirdparty' --instr-profile merged.profdata
              bin/fintamath_tests -format lcov > lcov.info
      COMMAND genhtml --branch-coverage lcov.info -o coverage
      DEPENDS ${PROJECT_NAME}_tests
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  endif()
endif()
