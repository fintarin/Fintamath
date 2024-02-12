#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/Exception.hpp"

using namespace fintamath;

TEST(ExceptionTests, whatTest) {
  EXPECT_THAT(
      [] { throw Exception(); },
      testing::ThrowsMessage<Exception>(
          testing::StrEq("Something went wrong...")));
}
