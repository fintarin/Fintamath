add_subdirectory(math_objects)
add_subdirectory(solver)

if(BUILD_APP)
  add_subdirectory(presenter)
  add_subdirectory(ui)
endif()
