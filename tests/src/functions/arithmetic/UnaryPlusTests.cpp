#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(UnaryPlusTests, toStringTest) {
  EXPECT_EQ(UnaryPlus().toString(), "+");
}

TEST(UnaryPlusTests, getFunctionTypeTest) {
  EXPECT_EQ(UnaryPlus().getFunctionType(), IFunction::Type::Unary);
}

TEST(UnaryPlusTests, getOperatorPriorityTest) {
  EXPECT_EQ(UnaryPlus().getOperatorPriority(), IOperator::Priority::PrefixUnary);
}

TEST(UnaryPlusTests, callTest) {
  EXPECT_EQ(UnaryPlus()(Integer(3)).toString(), "3");
  EXPECT_EQ(UnaryPlus()(Rational(5, 2)).toString(), "5/2");

  EXPECT_EQ(UnaryPlus()(Variable("a")).toString(), "a");

  std::unique_ptr<IOperator> o = std::make_unique<UnaryPlus>();
  EXPECT_ANY_THROW((*o)(Integer(1), Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
