file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp"
  "src/*.hpp")

add_executable(${PROJECT_NAME}_presenter ${SOURCES})
target_include_directories(${PROJECT_NAME}_presenter PRIVATE src)
target_link_libraries(${PROJECT_NAME}_presenter PRIVATE ${PROJECT_NAME}_solver)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
