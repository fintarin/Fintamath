#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

using namespace fintamath;

TEST(InvalidInputUnaryOpearatorExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw InvalidInputUnaryOperatorException("!", "-10", InvalidInputUnaryOperatorException::Type::Prefix); },
      testing::ThrowsMessage<InvalidInputUnaryOperatorException>(
          testing::StrEq("Invalid input: !(-10)")));
  EXPECT_THAT(
      [] { throw InvalidInputUnaryOperatorException("!", "-10", InvalidInputUnaryOperatorException::Type::Postfix); },
      testing::ThrowsMessage<InvalidInputUnaryOperatorException>(
          testing::StrEq("Invalid input: (-10)!")));
}
