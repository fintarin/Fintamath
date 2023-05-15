#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Abs f;

TEST(AbsTests, toStringTest) {
  EXPECT_EQ(f.toString(), "abs");
}

TEST(AbsTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AbsTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "10");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "abs(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AbsTests, doArgsMatchTest) {
  EXPECT_FALSE(f.doArgsMatch({}));
}

TEST(AbsTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Abs());
  EXPECT_EQ(Abs(), f);
  EXPECT_NE(f, Sin());
  EXPECT_NE(Sin(), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
}
