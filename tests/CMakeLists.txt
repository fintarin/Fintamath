file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_tests ${SOURCES})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
