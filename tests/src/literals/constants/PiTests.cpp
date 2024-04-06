#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const Pi c;

TEST(PiTests, toStringTest) {
  EXPECT_EQ(c.toString(), "Pi");
}

TEST(PiTests, callTest) {
  EXPECT_EQ(c()->toString(), "3.1415926535897932385");
}

TEST(PiTests, getClassTest) {
  EXPECT_EQ(c.getClass()->getName(), "Pi");
  EXPECT_EQ(c.getClass()->getParent(), IConstant::getClassStatic());
}
