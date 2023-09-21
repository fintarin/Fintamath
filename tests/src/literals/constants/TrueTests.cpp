#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/True.hpp"

using namespace fintamath;

const True c;

TEST(TrueTests, toStringTest) {
  EXPECT_EQ(c.toString(), "True");
}

TEST(TrueTests, callTest) {
  EXPECT_EQ(c()->toString(), "True");
  EXPECT_TRUE(is<Boolean>(c()));
}

TEST(TrueTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, True());
  EXPECT_EQ(True(), c);
  EXPECT_EQ(c, cast<IMathObject>(True()));
  EXPECT_EQ(cast<IMathObject>(True()), c);
  EXPECT_NE(c, E());
  EXPECT_NE(E(), c);
}

TEST(TrueTests, getTypeTest) {
  EXPECT_EQ(True::getTypeStatic(), MathObjectType::True);
  EXPECT_EQ(True().getType(), MathObjectType::True);
}
