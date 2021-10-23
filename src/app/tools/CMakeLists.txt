file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "fintamath_console/*.cpp"
  "fintamath_console/*.hpp")

add_executable(${PROJECT_NAME}_console ${SRC_LIST})

target_include_directories(${PROJECT_NAME}_console PRIVATE fintamath)

target_link_libraries(${PROJECT_NAME}_console PRIVATE ${PROJECT_NAME}_lib)
