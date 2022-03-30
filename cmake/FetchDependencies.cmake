# Fetch project dependencies

include(FetchContent)

# Fetch GTest
if(${PROJECT_NAME}_build_tests)
  message(STATUS "Fetching GTest...")
  FetchContent_Declare(googletest
                       URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  message(STATUS "GTest fetched")
endif()
