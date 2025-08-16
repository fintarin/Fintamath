include(../cmake/SuppressCompilerWarnings.cmake)
include(../cmake/ClangFormat.cmake)

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(${PROJECT_NAME}_tests ${SOURCES})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}::${PROJECT_NAME} GTest::gtest_main
                                                    GTest::gmock_main)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

suppress_compiler_warnings(${PROJECT_NAME}_tests)

target_clangformat_setup(${PROJECT_NAME}_tests)

if(MSVC)
  target_compile_options(${PROJECT_NAME}_tests PRIVATE /bigobj)
endif()
