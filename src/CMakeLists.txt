add_subdirectory(lib)

if(BUILD_APP)
  add_subdirectory(app)
endif()

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
