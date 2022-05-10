#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/literals/constants/Constant.hpp"

using namespace fintamath;

TEST(ConstantTests, equalsTests) {
  ConstantPtr c1 = std::make_unique<E>();
  ConstantPtr c2 = std::make_unique<Pi>();

  EXPECT_EQ(*c1, *c1);
  EXPECT_EQ(*c2, *c2);
  EXPECT_NE(*c1, *c2);
  EXPECT_NE(*c2, *c1);
}
