#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/exceptions/InvalidInputFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Div f;

TEST(DivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "/");
}

TEST(DivTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(DivTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Multiplication);
}

TEST(DivTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "3/2");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3/a");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
