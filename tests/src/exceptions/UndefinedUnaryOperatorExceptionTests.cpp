#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(UndefinedUnaryOpearatorExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw UndefinedUnaryOperatorException("!", "-10", UndefinedUnaryOperatorException::Type::Prefix); },
      testing::ThrowsMessage<UndefinedUnaryOperatorException>(
          testing::StrEq("Undefined: !(-10)")));
  EXPECT_THAT(
      [] { throw UndefinedUnaryOperatorException("!", "-10", UndefinedUnaryOperatorException::Type::Postfix); },
      testing::ThrowsMessage<UndefinedUnaryOperatorException>(
          testing::StrEq("Undefined: (-10)!")));
}
