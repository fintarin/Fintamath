file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp"
  "src/*.hpp")

add_library(${PROJECT_NAME}_math_objects ${SOURCES})
target_include_directories(${PROJECT_NAME}_math_objects PUBLIC src)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
