#include "gtest/gtest.h"

#include "fintamath/functions/comparison/More.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MoreTests, toStringTest) {
  EXPECT_EQ(More().toString(), ">");
}

TEST(MoreTests, getFunctionTypeTest) {
  EXPECT_EQ(More().getFunctionType(), IFunction::Type::Binary);
}

TEST(MoreTests, getOperatorPriorityTest) {
  EXPECT_EQ(More().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(MoreTests, callTest) {
  EXPECT_EQ(More()(Integer(5), Integer(3)).toString(), "true");
  EXPECT_EQ(More()(Integer(3), Integer(5)).toString(), "false");
  EXPECT_EQ(More()(Integer(3), Integer(3)).toString(), "false");
  EXPECT_EQ(More()(Integer(3), Rational(3, 1)).toString(), "false");
  EXPECT_EQ(More()(Rational(5, 2), Integer(2)).toString(), "true");

  EXPECT_EQ(More()(Integer(3), Variable("a")).toString(), "-a+3>0");
  EXPECT_EQ(More()(Variable("a"), Variable("a")).toString(), "false");

  std::unique_ptr<IOperator> o = std::make_unique<More>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
