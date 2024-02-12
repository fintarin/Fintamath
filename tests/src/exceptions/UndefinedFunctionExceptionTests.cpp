#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(UndefinedFunctionExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw UndefinedFunctionException("f", {}); },
      testing::ThrowsMessage<UndefinedFunctionException>(
          testing::StrEq("Undefined: f()")));
  EXPECT_THAT(
      [] { throw UndefinedFunctionException("sqrt", {"-10", "a", "b"}); },
      testing::ThrowsMessage<UndefinedFunctionException>(
          testing::StrEq("Undefined: sqrt(-10,a,b)")));
}
