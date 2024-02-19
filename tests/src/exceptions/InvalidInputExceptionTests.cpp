#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

using namespace fintamath;

TEST(InvalidInputExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw InvalidInputException(R"(Integer("abc"))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Integer("abc"))")));
}
