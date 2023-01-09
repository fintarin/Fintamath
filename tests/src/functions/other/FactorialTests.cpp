#include "gtest/gtest.h"

#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Factorial f;

TEST(FactorialTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!");
}

TEST(FactorialTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(FactorialTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(FactorialTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(), "3628800");

  EXPECT_EQ(f(Variable("a"))->toString(), "a!");

  EXPECT_THROW(f(Integer(-10)), UndefinedUnaryOpearatorException);
  EXPECT_THROW(f(Rational(1, 10)), UndefinedUnaryOpearatorException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
