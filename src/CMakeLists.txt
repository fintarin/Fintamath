add_subdirectory(lib)
add_subdirectory(app)

if(ENABLE_TESTING)
  add_subdirectory(tests)
endif()
