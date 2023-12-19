set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/mpfr-gmp-prebuilt
    PARENT_SCOPE)

add_subdirectory(boost-multiprecision)
get_target_property(BOOST_MULTIPRECISION_INCLUDE_DIR boost_multiprecision INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(boost_multiprecision SYSTEM INTERFACE ${BOOST_MULTIPRECISION_INCLUDE_DIR})
mark_as_advanced(BOOST_MULTIPRECISION_INCLUDE_DIR)

add_subdirectory(boost-math)
get_target_property(BOOST_MATH_INCLUDE_DIR boost_math INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(boost_math SYSTEM INTERFACE ${BOOST_MATH_INCLUDE_DIR})
mark_as_advanced(BOOST_MATH_INCLUDE_DIR)
