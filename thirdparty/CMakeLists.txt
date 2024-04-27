function(suppress_warnings lib)
  get_target_property(lib_type ${lib} TYPE)

  if(${lib_type} STREQUAL "INTERFACE_LIBRARY")
    get_target_property(lib_include_dir ${lib} INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(${lib} SYSTEM INTERFACE ${lib_include_dir})
  else()
    if(MSVC)
      target_compile_options(${lib} PRIVATE "/w")
    else()
      target_compile_options(${lib} PRIVATE "-w")
    endif()
  endif()
endfunction()

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/mpfr-gmp-prebuilt
    PARENT_SCOPE)

add_subdirectory(fmt)
suppress_warnings(fmt-header-only)

add_subdirectory(cppcoro)
suppress_warnings(cppcoro)

add_subdirectory(boost-multiprecision)
suppress_warnings(boost_multiprecision)

add_subdirectory(boost-math)
suppress_warnings(boost_math)

if(${PROJECT_NAME}_build_tests)
  add_subdirectory(googletest)
endif()
