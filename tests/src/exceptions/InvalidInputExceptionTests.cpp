#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

using namespace fintamath;

TEST(InvalidInputExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw InvalidInputException("Invalid input"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Invalid input")));
}
