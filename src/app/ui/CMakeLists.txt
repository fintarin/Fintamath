set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
set(CMAKE_AUTORCC ON)

find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED)

file(
  GLOB_RECURSE
  SRC_LIST
  CONFIGURE_DEPENDS
  "fintamath/*.cpp"
  "fintamath/*.hpp"
  "ui/*.ui"
  "resources/*.qrc")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE fintamath)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib Qt5::Widgets)

add_definitions(-DFINTAMATH_CONSOLE_EXE="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_console")
