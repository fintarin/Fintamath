file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.c"
  "include/*.h")

add_library(${PROJECT_NAME}_gmp ${SOURCES})

target_include_directories(${PROJECT_NAME}_gmp PUBLIC include)
