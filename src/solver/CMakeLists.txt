file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp"
  "src/*.hpp")

add_library(${PROJECT_NAME}_solver ${SOURCES})
target_include_directories(${PROJECT_NAME}_solver PUBLIC src)
target_link_libraries(${PROJECT_NAME}_solver PUBLIC ${PROJECT_NAME}_math_objects)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
