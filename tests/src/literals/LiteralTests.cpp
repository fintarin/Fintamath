#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/ILiteral.hpp"

#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(LiteralTests, equalsTests) {
  LiteralPtr c1 = std::make_unique<Boolean>(std::string("true"));
  LiteralPtr c2 = std::make_unique<Variable>("a");
  LiteralPtr c3 = std::make_unique<Variable>("b");

  EXPECT_EQ(*c1, *c1);
  EXPECT_EQ(*c2, *c2);
  EXPECT_NE(*c1, *c2);
  EXPECT_NE(*c2, *c1);

  EXPECT_EQ(*c2, *c2);
  EXPECT_EQ(*c3, *c3);
  EXPECT_NE(*c2, *c3);
  EXPECT_NE(*c3, *c2);

  EXPECT_NE(*c1, *c2);
  EXPECT_NE(*c1, *c2);
}

TEST(LiteralTests, parseTest) {
  EXPECT_TRUE(ILiteral::parse("a")->is<Variable>());
  EXPECT_TRUE(ILiteral::parse("z")->is<Variable>());
  EXPECT_TRUE(ILiteral::parse("true")->is<Boolean>());
  EXPECT_TRUE(ILiteral::parse("false")->is<Boolean>());

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
}
