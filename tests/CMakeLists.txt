file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_tests ${SOURCES})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} gtest_main nlohmann_json::nlohmann_json)

gtest_discover_tests(${PROJECT_NAME}_tests)

add_custom_command(
  TARGET ${PROJECT_NAME}_tests
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/
  COMMAND ${CMAKE_COMMAND} -E copy_directory resources ${CMAKE_CURRENT_BINARY_DIR}/resources/
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
