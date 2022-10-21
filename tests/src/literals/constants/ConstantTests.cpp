#include <gtest/gtest.h>

#include "fintamath/literals/constants/IConstant.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(ConstantTests, equalsTests) {
  ConstantPtr c1 = std::make_unique<E>();
  ConstantPtr c2 = std::make_unique<Pi>();

  EXPECT_EQ(*c1, *c1);
  EXPECT_EQ(*c2, *c2);
  EXPECT_NE(*c1, *c2);
  EXPECT_NE(*c2, *c1);
}

TEST(ConstantTests, parseTest) {
  EXPECT_TRUE(IConstant::parse("e")->is<E>());
  EXPECT_TRUE(IConstant::parse("pi")->is<Pi>());

  EXPECT_EQ(IConstant::parse("a"), nullptr);
  EXPECT_EQ(IConstant::parse("z"), nullptr);
  EXPECT_EQ(IConstant::parse("1"), nullptr);
  EXPECT_EQ(IConstant::parse("a_"), nullptr);
  EXPECT_EQ(IConstant::parse("a1"), nullptr);
  EXPECT_EQ(IConstant::parse("aa"), nullptr);
}
