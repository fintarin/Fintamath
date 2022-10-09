# Fetch project dependencies

include(FetchContent)

# Find GMP
find_package(GMP REQUIRED)

# Fetch GTest
if(${PROJECT_NAME}_build_tests)
  message(STATUS "Fetching GTest...")

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)

  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  message(STATUS "GTest fetched")
endif()
