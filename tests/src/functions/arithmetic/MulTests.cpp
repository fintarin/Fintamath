#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MulTests, toStringTest) {
  EXPECT_EQ(Mul().toString(), "*");
}

TEST(MulTests, getFunctionTypeTest) {
  EXPECT_EQ(Mul().getFunctionType(), IFunction::Type::Binary);
}

TEST(MulTests, getOperatorPriorityTest) {
  EXPECT_EQ(Mul().getOperatorPriority(), IOperator::Priority::Multiplication);
}

TEST(MulTests, callTest) {
  EXPECT_EQ(Mul()(Integer(3), Integer(5)).toString(), "15");
  EXPECT_EQ(Mul()(Integer(3), Rational(5, 2)).toString(), "15/2");
  EXPECT_EQ(Mul()(Rational(5, 2), Integer(3)).toString(), "15/2");
  EXPECT_EQ(Mul()(Rational(5, 2), Rational(5, 3)).toString(), "25/6");

  EXPECT_EQ(Mul()(Integer(3), Variable("a")).toString(), "3*a");

  std::unique_ptr<IOperator> o = std::make_unique<Mul>();
  EXPECT_THROW((*o)(Integer(1)), FunctionCallException);
  EXPECT_THROW((*o)(Rational(2, 3)), FunctionCallException);
  EXPECT_THROW((*o)(), FunctionCallException);
  EXPECT_THROW((*o)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}

TEST(MulTests, getClassNameTest) {
  EXPECT_EQ(Mul().getClassName(), "Mul");
}
