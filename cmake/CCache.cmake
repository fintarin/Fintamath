# Enable ccache

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
  option(${PROJECT_NAME}_enable_ccache "Enable ccache" ON)
  if(${PROJECT_NAME}_enable_ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()
