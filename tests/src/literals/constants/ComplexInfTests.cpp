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

TEST(ComplexInfTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, ComplexInf());
  EXPECT_EQ(ComplexInf(), c);
  EXPECT_EQ(c, cast<IMathObject>(ComplexInf()));
  EXPECT_EQ(cast<IMathObject>(ComplexInf()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(ComplexInfTests, getTypeIdTest) {
  EXPECT_EQ(ComplexInf::getTypeIdStatic(), MathObjectTypeId(MathObjectType::ComplexInf));
  EXPECT_EQ(ComplexInf().getTypeId(), MathObjectTypeId(MathObjectType::ComplexInf));
}
