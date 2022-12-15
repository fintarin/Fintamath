#include "gtest/gtest.h"

#include "fintamath/functions/comparison/MoreEqv.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MoreEqvTests, toStringTest) {
  EXPECT_EQ(MoreEqv().toString(), ">=");
}

TEST(MoreEqvTests, getFunctionTypeTest) {
  EXPECT_EQ(MoreEqv().getFunctionType(), IFunction::Type::Binary);
}

TEST(MoreEqvTests, getOperatorPriorityTest) {
  EXPECT_EQ(MoreEqv().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(MoreEqvTests, callTest) {
  EXPECT_EQ(MoreEqv()(Integer(5), Integer(3)).toString(), "true");
  EXPECT_EQ(MoreEqv()(Integer(3), Integer(5)).toString(), "false");
  EXPECT_EQ(MoreEqv()(Integer(3), Integer(3)).toString(), "true");
  EXPECT_EQ(MoreEqv()(Integer(3), Rational(3, 1)).toString(), "true");
  EXPECT_EQ(MoreEqv()(Rational(5, 2), Integer(2)).toString(), "true");

  // TODO: uncomment this
  // EXPECT_EQ(MoreEqv()(Integer(3), Variable("a")).toString(), "-a+3>=0");
  // EXPECT_EQ(MoreEqv()(Variable("a"), Variable("a")).toString(), "true");

  std::unique_ptr<IOperator> o = std::make_unique<MoreEqv>();
  EXPECT_THROW((*o)(Integer(1)), FunctionCallException);
  EXPECT_THROW((*o)(Rational(2, 3)), FunctionCallException);
  EXPECT_THROW((*o)(), FunctionCallException);
  EXPECT_THROW((*o)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}
