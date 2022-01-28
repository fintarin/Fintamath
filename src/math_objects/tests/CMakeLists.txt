file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_math_objects_tests ${SOURCES})
target_link_libraries(${PROJECT_NAME}_math_objects_tests PRIVATE ${PROJECT_NAME}_math_objects GTest::gtest_main)
gtest_discover_tests(${PROJECT_NAME}_math_objects_tests)

add_definitions(-DRESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
