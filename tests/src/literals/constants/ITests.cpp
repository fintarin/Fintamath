#include <gtest/gtest.h>

#include "fintamath/literals/constants/I.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const I c;

TEST(ITests, toStringTest) {
  EXPECT_EQ(c.toString(), "I");
}

TEST(ITests, callTest) {
  EXPECT_EQ(c()->toString(), "I");
}

TEST(ITests, getClassTest) {
  EXPECT_EQ(c.getClass(), MathObjectClass("I"));
  EXPECT_EQ(c.getClass().getParent(), IConstant::getClassStatic());
}
