#include "gtest/gtest.h"

#include "fintamath/functions/factorials/DoubleFactorial.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(DoubleFactorialTests, toStringTest) {
  EXPECT_EQ(DoubleFactorial().toString(), "!!");
}

TEST(DoubleFactorialTests, getFunctionTypeTest) {
  EXPECT_EQ(DoubleFactorial().getFunctionType(), IFunction::Type::Unary);
}

TEST(DoubleFactorialTests, getOperatorPriorityTest) {
  EXPECT_EQ(DoubleFactorial().getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(DoubleFactorialTests, callTest) {
  EXPECT_EQ(DoubleFactorial()(Integer(0))->toString(), "1");
  EXPECT_EQ(DoubleFactorial()(Integer(1))->toString(), "1");
  EXPECT_EQ(DoubleFactorial()(Integer(5))->toString(), "15");
  EXPECT_EQ(DoubleFactorial()(Integer(10))->toString(), "3840");

  EXPECT_ANY_THROW(DoubleFactorial()(Variable("a")));
  EXPECT_ANY_THROW(DoubleFactorial()(Integer(-10)));
  EXPECT_ANY_THROW(DoubleFactorial()(Rational(1, 10)));

  std::unique_ptr<IFunction> f = std::make_unique<DoubleFactorial>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "3840");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}