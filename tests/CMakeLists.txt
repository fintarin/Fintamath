add_definitions(-DRESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_tests ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib GTest::gtest_main)
