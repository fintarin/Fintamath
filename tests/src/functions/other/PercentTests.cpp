#include "gtest/gtest.h"

#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Percent f;

TEST(PercentTests, toStringTest) {
  EXPECT_EQ(f.toString(), "%");
}

TEST(PercentTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(PercentTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(PercentTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1/100");
  EXPECT_EQ(f(Integer(1000))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "-1/10");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "1/1000");

  EXPECT_EQ(f(Variable("a"))->toString(), "1/100 a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
