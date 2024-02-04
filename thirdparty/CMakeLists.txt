function(mark_include_directories_as_system lib)
  get_target_property(lib_include_dir ${lib} INTERFACE_INCLUDE_DIRECTORIES)
  target_include_directories(${lib} SYSTEM INTERFACE ${lib_include_dir})
endfunction()

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/mpfr-gmp-prebuilt
    PARENT_SCOPE)

add_subdirectory(boost-multiprecision)
mark_include_directories_as_system(boost_multiprecision)

add_subdirectory(boost-math)
mark_include_directories_as_system(boost_math)

if(${PROJECT_NAME}_build_tests)
  add_subdirectory(googletest)
endif()
