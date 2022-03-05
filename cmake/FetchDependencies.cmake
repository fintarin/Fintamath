# Fetch project dependencies

include(FetchContent)

# Fetch Json
message(STATUS "Fetching Json...")
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.10.5)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
message(STATUS "Json fetched")

# Fetch GTest
if(${PROJECT_NAME}_enable_tests)
  message(STATUS "Fetching GTest...")
  FetchContent_Declare(googletest
                       URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  message(STATUS "GTest fetched")
endif()
