#include <gtest/gtest.h>

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const ComplexInf c;

TEST(ComplexInfTests, toStringTest) {
  EXPECT_EQ(c.toString(), "ComplexInf");
}

TEST(ComplexInfTests, callTest) {
  EXPECT_EQ(c()->toString(), "ComplexInf");
}

TEST(ComplexInfTests, getClassTest) {
  EXPECT_EQ(ComplexInf::getClassStatic(), MathObjectClass("ComplexInf"));
  EXPECT_EQ(ComplexInf::getClassStatic().getParent(), IConstant::getClassStatic());
}
