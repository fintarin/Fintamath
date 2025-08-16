include(../cmake/SuppressCompilerWarnings.cmake)

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "src/*.cpp")

foreach(source ${SOURCES})
  get_filename_component(bench ${source} NAME_WE)
  add_executable(${PROJECT_NAME}_${bench} ${source})

  target_link_libraries(${PROJECT_NAME}_${bench} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME} benchmark::benchmark)

  set_target_properties(${PROJECT_NAME}_${bench} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

  suppress_compiler_warnings(${PROJECT_NAME}_${bench})

  target_clangformat_setup(${PROJECT_NAME}_${bench})
endforeach()
