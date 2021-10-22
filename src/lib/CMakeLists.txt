file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "fintamath/*.cpp"
  "fintamath/*.hpp")

add_library(${PROJECT_NAME}_lib ${SRC_LIST})

target_include_directories(${PROJECT_NAME}_lib PUBLIC fintamath)
