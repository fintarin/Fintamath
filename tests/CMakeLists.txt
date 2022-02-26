file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_tests ${SOURCES})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::gtest_main nlohmann_json::nlohmann_json)

gtest_discover_tests(${PROJECT_NAME}_tests)
