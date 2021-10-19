file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "fintamath/*.cpp"
  "fintamath/*.hpp")

add_library(${PROJECT_NAME}_lib ${SRC_LIST})

target_include_directories(${PROJECT_NAME}_lib PUBLIC fintamath)

file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "main/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
