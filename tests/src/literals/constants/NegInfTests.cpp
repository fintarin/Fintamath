#include <gtest/gtest.h>

#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const NegInf c;

TEST(NegInfTests, toStringTest) {
  EXPECT_EQ(c.toString(), "-Inf");
}

TEST(NegInfTests, callTest) {
  EXPECT_EQ(c()->toString(), "-Inf");
}

TEST(NegInfTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, NegInf());
  EXPECT_EQ(NegInf(), c);
  EXPECT_EQ(c, cast<IMathObject>(NegInf()));
  EXPECT_EQ(cast<IMathObject>(NegInf()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(NegInfTests, getTypeIdTest) {
  EXPECT_EQ(NegInf::getTypeIdStatic(), MathObjectTypeId(MathObjectType::NegInf));
  EXPECT_EQ(NegInf().getTypeId(), MathObjectTypeId(MathObjectType::NegInf));
}
