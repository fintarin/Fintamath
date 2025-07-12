# Enable coverage

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(${PROJECT_NAME}_enable_coverage "Enable coverage reporting for gcc/clang" OFF)
  if(${PROJECT_NAME}_enable_coverage)
    find_program(LCOV_PROGRAM lcov REQUIRED)
    find_program(GENHTML_PROGRAM genhtml REQUIRED)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fno-elide-constructors -fno-inline -O0")

    set(coverage_dirs_include
        --include
        '${CMAKE_SOURCE_DIR}/include/*'
        --include
        '${CMAKE_SOURCE_DIR}/src/*')

    add_custom_target(
      ${PROJECT_NAME}_coverage
      COMMAND ${LCOV_PROGRAM} --capture --initial --directory . ${coverage_dirs_include} --output-file lcov_base.info
              --ignore-errors mismatch
      COMMAND ./bin/fintamath_tests
      COMMAND ${LCOV_PROGRAM} --capture --directory . ${coverage_dirs_include} --output-file lcov_test.info --rc
              branch_coverage=1 --ignore-errors mismatch
      COMMAND ${LCOV_PROGRAM} --add-tracefile lcov_base.info --add-tracefile lcov_test.info --output-file
              lcov_total.info --rc branch_coverage=1
      COMMAND ${GENHTML_PROGRAM} --title "Fintamath" --legend --demangle-cpp --output-directory html --show-details
              --branch-coverage lcov_total.info
      DEPENDS ${PROJECT_NAME}_tests
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

    unset(coverage_dirs_include)
  endif()
endif()
