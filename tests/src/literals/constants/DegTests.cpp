#include <gtest/gtest.h>

#include "fintamath/literals/constants/Deg.hpp"

#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const Deg c;

TEST(DegTests, toStringTest) {
  EXPECT_EQ(c.toString(), "Deg");
}

TEST(DegTests, callTest) {
  EXPECT_EQ(c()->toString(), "Pi/180");
}

TEST(DegTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, Deg());
  EXPECT_EQ(Deg(), c);
  EXPECT_EQ(c, cast<IMathObject>(Deg()));
  EXPECT_EQ(cast<IMathObject>(Deg()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(DegTests, getTypeIdTest) {
  EXPECT_EQ(Deg::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Deg));
  EXPECT_EQ(Deg().getTypeId(), MathObjectTypeId(MathObjectType::Deg));
}
