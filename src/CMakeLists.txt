file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "fintamath/*.cpp"
  "fintamath/*.hpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_gmp)
