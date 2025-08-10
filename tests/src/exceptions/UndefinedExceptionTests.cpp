#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(UndefinedExceptionTests, whatTest) {
  EXPECT_THAT(
    [] { throw UndefinedException("Undefined"); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq("Undefined")
    )
  );
}
