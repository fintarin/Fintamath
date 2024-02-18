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

TEST(UndefinedTests, getTypeTest) {
  EXPECT_EQ(Undefined::getTypeStatic(), MathObjectType(MathObjectType::Undefined, "Undefined"));
  EXPECT_EQ(Undefined().getType(), MathObjectType(MathObjectType::Undefined, "Undefined"));
}
