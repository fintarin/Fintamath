#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/ILiteral.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(LiteralTests, equalsTests) {
  LiteralPtr c1 = std::make_unique<E>();
  LiteralPtr c2 = std::make_unique<Pi>();
  LiteralPtr v1 = std::make_unique<Variable>("a");
  LiteralPtr v2 = std::make_unique<Variable>("b");

  EXPECT_EQ(*c1, *c1);
  EXPECT_EQ(*c2, *c2);
  EXPECT_NE(*c1, *c2);
  EXPECT_NE(*c2, *c1);

  EXPECT_EQ(*v1, *v1);
  EXPECT_EQ(*v2, *v2);
  EXPECT_NE(*v1, *v2);
  EXPECT_NE(*v2, *v1);

  EXPECT_NE(*c1, *v1);
  EXPECT_NE(*c1, *v1);
}

TEST(LiteralTests, parseTest) {
  EXPECT_TRUE(ILiteral::parse("e")->is<E>());
  EXPECT_TRUE(ILiteral::parse("pi")->is<Pi>());
  EXPECT_TRUE(ILiteral::parse("a")->is<Variable>());
  EXPECT_TRUE(ILiteral::parse("z")->is<Variable>());
  EXPECT_TRUE(ILiteral::parse("true")->is<Boolean>());
  EXPECT_TRUE(ILiteral::parse("false")->is<Boolean>());

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
}
