file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "fintamath/*.cpp"
  "fintamath/*.hpp")

if(${PROJECT_NAME}_build_shared)
  add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
  add_library(${PROJECT_NAME} ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::multiprecision)
