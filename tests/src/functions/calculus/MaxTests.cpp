#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Max.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Max f;

TEST(MaxTests, toStringTest) {
  EXPECT_EQ(f.toString(), "max");
}

TEST(MaxTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Any);
}

TEST(MaxTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1), Rational(-5, 2))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Rational(5, 2), Rational(-5, 2), Integer(-1))->toString(), "5/2");

  EXPECT_EQ(f(Rational(-1), Variable("x"), Variable("y"), Integer(1))->toString(), "max(x, y, 1)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
}
