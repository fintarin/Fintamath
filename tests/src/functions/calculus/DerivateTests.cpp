#include "gtest/gtest.h"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/calculus/Derivate.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(DerivateTests, toStringTest) {
  EXPECT_EQ(Derivate().toString(), "'");
}

TEST(DerivateTests, getFunctionTypeTest) {
  EXPECT_EQ(Derivate().getFunctionType(), IFunction::Type::Unary);
}

TEST(DerivateTests, getOperatorPriorityTest) {
  EXPECT_EQ(Derivate().getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(DerivateTests, callTest) {
  EXPECT_EQ(Derivate()(Variable("a"))->toString(), "1");
  EXPECT_EQ(Derivate()(Expression("a+a"))->toString(), "(2*a)'");
  EXPECT_EQ(Derivate()(Integer(5))->toString(), "0");

  std::unique_ptr<IFunction> f = std::make_unique<Derivate>();
  EXPECT_EQ((*f)(Integer(5))->toString(), "0");
  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
