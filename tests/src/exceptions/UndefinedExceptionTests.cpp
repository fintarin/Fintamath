#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(UndefinedExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw UndefinedException(); },
      testing::ThrowsMessage<UndefinedException>(
          testing::StrEq("Undefined")));
  EXPECT_THAT(
      [] { throw UndefinedException("123"); },
      testing::ThrowsMessage<UndefinedException>(
          testing::StrEq("Undefined: 123")));
}