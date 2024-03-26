#include <gtest/gtest.h>

#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

using namespace fintamath;

const Undefined c;

TEST(UndefinedTests, toStringTest) {
  EXPECT_EQ(c.toString(), "Undefined");
}

TEST(UndefinedTests, callTest) {
  EXPECT_EQ(c()->toString(), "Undefined");
}

TEST(UndefinedTests, getClassTest) {
  EXPECT_EQ(Undefined::getClassStatic(), MathObjectClass("Undefined"));
  EXPECT_EQ(Undefined::getClassStatic().getParent(), IConstant::getClassStatic());
}
