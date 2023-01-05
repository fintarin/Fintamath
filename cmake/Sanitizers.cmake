# Enable sanitizers

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(${PROJECT_NAME}_enable_sanitizers "Enable sanitizers" OFF)
  if(${PROJECT_NAME}_enable_sanitizers)
    set(sanitizers "address,undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${sanitizers}")
  endif()
endif()
