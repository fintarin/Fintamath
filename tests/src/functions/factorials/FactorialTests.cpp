#include "gtest/gtest.h"

#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(FactorialTests, toStringTest) {
  EXPECT_EQ(Factorial().toString(), "!");
}

TEST(FactorialTests, getFunctionTypeTest) {
  EXPECT_EQ(Factorial().getFunctionType(), IFunction::Type::Unary);
}

TEST(FactorialTests, getOperatorPriorityTest) {
  EXPECT_EQ(Factorial().getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(FactorialTests, callTest) {
  EXPECT_EQ(Factorial()(Integer(0)).toString(), "1");
  EXPECT_EQ(Factorial()(Integer(1)).toString(), "1");
  EXPECT_EQ(Factorial()(Integer(10)).toString(), "3628800");

  EXPECT_EQ(Factorial()(Variable("a")).toString(), "a!");

  EXPECT_THROW(Factorial()(Integer(-10)), UndefinedUnaryOpearatorException);
  EXPECT_THROW(Factorial()(Rational(1, 10)), UndefinedUnaryOpearatorException);

  std::unique_ptr<IFunction> f = std::make_unique<Factorial>();
  EXPECT_EQ((*f)(Integer(5)).toString(), "120");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}
