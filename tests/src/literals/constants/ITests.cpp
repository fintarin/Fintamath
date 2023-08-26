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

TEST(ITests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, I());
  EXPECT_EQ(I(), c);
  EXPECT_EQ(c, cast<IMathObject>(I()));
  EXPECT_EQ(cast<IMathObject>(I()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(ITests, getTypeIdTest) {
  EXPECT_EQ(I::getTypeIdStatic(), MathObjectTypeId(MathObjectType::I));
  EXPECT_EQ(I().getTypeId(), MathObjectTypeId(MathObjectType::I));
}
