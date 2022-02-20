# Prevent in source builds

function(prevent_in_source_builds)
  get_filename_component(src_dir ${CMAKE_SOURCE_DIR} REALPATH)
  get_filename_component(bin_dir ${CMAKE_BINARY_DIR} REALPATH)

  if(src_dir STREQUAL bin_dir)
    message(
      FATAL_ERROR "In-source builds are disabled, please create a separate build directory and run cmake from there")
  endif()
endfunction()

prevent_in_source_builds()
