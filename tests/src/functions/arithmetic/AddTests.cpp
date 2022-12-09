#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AddTests, toStringTest) {
  EXPECT_EQ(Add().toString(), "+");
}

TEST(AddTests, getFunctionTypeTest) {
  EXPECT_EQ(Add().getFunctionType(), IFunction::Type::Binary);
}

TEST(AddTests, getOperatorPriorityTest) {
  EXPECT_EQ(Add().getOperatorPriority(), IOperator::Priority::Addition);
}

TEST(AddTests, callTest) {
  EXPECT_EQ(Add()(Integer(3), Integer(5)).toString(), "8");
  EXPECT_EQ(Add()(Integer(3), Rational(5, 2)).toString(), "11/2");
  EXPECT_EQ(Add()(Rational(5, 2), Integer(3)).toString(), "11/2");
  EXPECT_EQ(Add()(Rational(5, 2), Rational(5, 2)).toString(), "5");
  EXPECT_EQ(Add()(Rational(5, 2), Rational(5, 3)).toString(), "25/6");

  EXPECT_EQ(Add()(Integer(3), Variable("a")).toString(), "a+3");

  std::unique_ptr<IOperator> o = std::make_unique<Add>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
