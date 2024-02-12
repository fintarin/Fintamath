#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

using namespace fintamath;

TEST(InvalidInputBinaryOpearatorExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw InvalidInputBinaryOperatorException("^", "a", "0"); },
      testing::ThrowsMessage<InvalidInputBinaryOperatorException>(
          testing::StrEq("Invalid input: (a)^(0)")));
}
