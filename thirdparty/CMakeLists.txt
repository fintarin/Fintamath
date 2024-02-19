function(mark_include_directories_as_system lib)
  get_target_property(lib_include_dir ${lib} INTERFACE_INCLUDE_DIRECTORIES)
  target_include_directories(${lib} SYSTEM INTERFACE ${lib_include_dir})
endfunction()

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/mpfr-gmp-prebuilt
    PARENT_SCOPE)

add_subdirectory(boost-config)
mark_include_directories_as_system(boost_config)
    
add_subdirectory(boost-mp11)
mark_include_directories_as_system(boost_mp11)

add_subdirectory(boost-describe)
mark_include_directories_as_system(boost_describe)

add_subdirectory(boost-container-hash)
mark_include_directories_as_system(boost_container_hash)

add_subdirectory(boost-multiprecision)
mark_include_directories_as_system(boost_multiprecision)

add_subdirectory(boost-math)
mark_include_directories_as_system(boost_math)

add_subdirectory(fmt)
mark_include_directories_as_system(fmt)

if(${PROJECT_NAME}_build_tests)
  add_subdirectory(googletest)
endif()
