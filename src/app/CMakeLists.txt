file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "fintamath/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
