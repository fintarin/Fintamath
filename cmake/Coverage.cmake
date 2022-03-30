# Enable coverage

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(${PROJECT_NAME}_enable_coverage "Enable coverage reporting for gcc/clang" OFF)
  if(${PROJECT_NAME}_enable_coverage)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")

    add_custom_target(
      ${PROJECT_NAME}_coverage
      COMMAND cd build && ctest -CDebug && cd ..
      COMMAND mkdir -p build/coverage
      COMMAND gcovr -r . -e ".*build/.*" -e ".*tests/.*" --exclude-throw-branches --html-details -o
              "${CMAKE_BINARY_DIR}/coverage/coverage.html"
      COMMAND gcovr -r . -e ".*build/.*" -e ".*tests/.*" --exclude-throw-branches --xml -o
              "${CMAKE_BINARY_DIR}/coverage/coverage.xml"
      COMMAND gcovr -r . -e ".*build/.*" -e ".*tests/.*" --exclude-throw-branches --sonarqube -o
              "${CMAKE_BINARY_DIR}/coverage/coverage_sonar.xml"
      DEPENDS ${PROJECT_NAME}_tests
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  endif()
endif()
