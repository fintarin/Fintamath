file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "fintamath/*.cpp"
  "fintamath/*.hpp")

add_executable(${PROJECT_NAME} ${SRC_LIST})

set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

target_include_directories(${PROJECT_NAME} PUBLIC fintamath)
