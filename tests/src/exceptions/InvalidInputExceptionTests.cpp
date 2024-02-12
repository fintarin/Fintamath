#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

using namespace fintamath;

TEST(InvalidInputExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw InvalidInputException(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Invalid input")));
  EXPECT_THAT(
      [] { throw InvalidInputException("123"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Invalid input: 123")));
}