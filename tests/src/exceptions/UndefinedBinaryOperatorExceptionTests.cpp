#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(UndefinedBinaryOpearatorExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw UndefinedBinaryOperatorException("^", "a", "0"); },
      testing::ThrowsMessage<UndefinedBinaryOperatorException>(
          testing::StrEq("Undefined: (a)^(0)")));
}
