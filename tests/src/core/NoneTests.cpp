#include <gtest/gtest.h>

#include "fintamath/core/None.hpp"

using namespace fintamath;

TEST(NoneTests, getClassTest) {
  EXPECT_FALSE(None::getClassStatic());
}
