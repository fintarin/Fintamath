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

TEST(UndefinedTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, Undefined());
  EXPECT_EQ(Undefined(), c);
  EXPECT_EQ(c, cast<IMathObject>(Undefined()));
  EXPECT_EQ(cast<IMathObject>(Undefined()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(UndefinedTests, getTypeIdTest) {
  EXPECT_EQ(Undefined::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Undefined));
  EXPECT_EQ(Undefined().getTypeId(), MathObjectTypeId(MathObjectType::Undefined));
}
