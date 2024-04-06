#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const False c;

TEST(FalseTests, toStringTest) {
  EXPECT_EQ(c.toString(), "False");
}

TEST(FalseTests, callTest) {
  EXPECT_EQ(c()->toString(), "False");
  EXPECT_TRUE(is<Boolean>(c()));
}

TEST(FalseTests, getClassTest) {
  EXPECT_EQ(c.getClass()->getName(), "False");
  EXPECT_EQ(c.getClass()->getParent(), IConstant::getClassStatic());
}
