# Fetch project dependencies

include(FetchContent)

# Find GMP
find_package(GMP REQUIRED)

# Fetch Eigen3
if(NOT TARGET Eigen3::Eigen)
  FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

  set(EIGEN_BUILD_DOC OFF)
  set(BUILD_TESTING OFF)
  set(EIGEN_BUILD_PKGCONFIG OFF)
  set(OFF)
  
  FetchContent_MakeAvailable(Eigen)
endif()

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
