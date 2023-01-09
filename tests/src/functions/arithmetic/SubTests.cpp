#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Sub.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Sub f;

TEST(SubTests, toStringTest) {
  EXPECT_EQ(f.toString(), "-");
}

TEST(SubTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(SubTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Addition);
}

TEST(SubTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "-2");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "1/2");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "-1/2");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 2))->toString(), "0");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "5/6");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "-a+3");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
