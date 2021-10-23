# Enable sanitizers

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_SANITIZERS "Enable sanitizers" OFF)
  if(ENABLE_SANITIZERS)
    set(sanitizers "address,undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=${sanitizers}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${sanitizers}")
  endif()
endif()
