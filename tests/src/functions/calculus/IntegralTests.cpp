#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Integral.hpp"

#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Integral f;

TEST(IntegralTests, toStringTest) {
  EXPECT_EQ(f.toString(), "integral");
}

TEST(IntegralTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(IntegralTests, callTest) {
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "1/2 a^2");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "integral(a, b)");
  EXPECT_EQ(f(Expression("a+a"), Variable("a"))->toString(), "integral(2 a, a)"); // TODO: integral
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "5 a");

  EXPECT_THROW(f(Integer(5), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+a")), InvalidInputException); // TODO: integral

  EXPECT_THROW(f(), InvalidInputException);
  EXPECT_THROW(f(Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputException);
}
