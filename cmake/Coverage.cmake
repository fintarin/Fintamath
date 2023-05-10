# Enable coverage

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(${PROJECT_NAME}_enable_coverage "Enable coverage reporting for gcc/clang" OFF)
  if(${PROJECT_NAME}_enable_coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")

    find_program(LCOV_TOOL NAMES lcov)

    add_custom_target(
      ${PROJECT_NAME}_coverage
      COMMAND cd build && ctest -CDebug && cd ..
      COMMAND ${LCOV_TOOL} --capture --directory . --output-file build/lcov_tmp.info --rc lcov_branch_coverage=1
      COMMAND ${LCOV_TOOL} --remove build/lcov_tmp.info '*/usr/*' '*/build/*' '*/tests/*' '*/thirdparty/*' --output-file
              build/lcov_tmp.info --rc lcov_branch_coverage=1
      COMMAND ${CMAKE_SOURCE_DIR}/tests/scripts/coverage_filter.py build/lcov_tmp.info > build/lcov.info
      COMMAND rm build/lcov_tmp.info
      COMMAND genhtml --output-directory build/coverage --show-details --branch-coverage build/lcov.info
      DEPENDS ${PROJECT_NAME}_tests
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  endif()
endif()
