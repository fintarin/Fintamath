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
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp"
  "src/*.hpp"
  "ui/*.ui"
  "resources/*.qrc")

add_executable(${PROJECT_NAME}_ui ${SOURCES})
target_include_directories(${PROJECT_NAME}_ui PRIVATE src)
target_link_libraries(${PROJECT_NAME}_ui PRIVATE Qt5::Widgets)

add_definitions(-DPRESENTER_BINARY="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_presenter")
