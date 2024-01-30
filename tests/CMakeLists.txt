file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_tests ${SOURCES}
        src/overall/approximate/ApproximateTests.cpp
        src/overall/solve/SolveTests.cpp
        src/overall/simplify/SimplifyTests.cpp
        src/overall/simplify/SimplifyInfinitiesTests.cpp
        src/overall/simplify/SimplifyTrigonometryTests.cpp
        src/overall/simplify/SimplifyHyperbolicTests.cpp
        src/overall/simplify/SimplifyFactorialsTests.cpp
        src/overall/simplify/SimplifyPowersTests.cpp)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} gtest_main)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

if(MSVC)
  target_compile_options(${PROJECT_NAME}_tests PRIVATE /w)
else()
  target_compile_options(${PROJECT_NAME}_tests PRIVATE -w)
endif()
