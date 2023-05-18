#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const Pi c;

TEST(PiTests, toStringTest) {
  EXPECT_EQ(c.toString(), "Pi");
}

TEST(PiTests, callTest) {
  EXPECT_EQ(c()->toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}

TEST(PiTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, Pi());
  EXPECT_EQ(Pi(), c);
  EXPECT_EQ(c, cast<IMathObject>(Pi()));
  EXPECT_EQ(cast<IMathObject>(Pi()), c);
  EXPECT_NE(c, E());
  EXPECT_NE(E(), c);
}

TEST(PiTests, getTypeIdTest) {
  EXPECT_EQ(Pi::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Pi));
  EXPECT_EQ(Pi().getTypeId(), MathObjectTypeId(MathObjectType::Pi));
}
