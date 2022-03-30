# Enable coverage

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(${PROJECT_NAME}_enable_coverage "Enable coverage reporting for gcc/clang" OFF)
  if(${PROJECT_NAME}_enable_coverage)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
  endif()
endif()
