add_subdirectory(multiprecision-Boost_1_80_0)

if(MSVC)
  target_compile_options(boost_multiprecision INTERFACE /w)
else()
  target_compile_options(boost_multiprecision INTERFACE -w)
endif()
