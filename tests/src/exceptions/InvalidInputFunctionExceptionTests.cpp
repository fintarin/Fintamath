#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

using namespace fintamath;

TEST(InvalidInputFunctionExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw InvalidInputFunctionException("f", {}); },
      testing::ThrowsMessage<InvalidInputFunctionException>(
          testing::StrEq("Invalid input: f()")));
  EXPECT_THAT(
      [] { throw InvalidInputFunctionException("sqrt", {"-10", "a", "b"}); },
      testing::ThrowsMessage<InvalidInputFunctionException>(
          testing::StrEq("Invalid input: sqrt(-10,a,b)")));
}
