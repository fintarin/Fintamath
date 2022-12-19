#include "gtest/gtest.h"

#include "fintamath/functions/comparison/Less.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(LessTests, toStringTest) {
  EXPECT_EQ(Less().toString(), "<");
}

TEST(LessTests, getFunctionTypeTest) {
  EXPECT_EQ(Less().getFunctionType(), IFunction::Type::Binary);
}

TEST(LessTests, getOperatorPriorityTest) {
  EXPECT_EQ(Less().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(LessTests, callTest) {
  EXPECT_EQ(Less()(Integer(5), Integer(3)).toString(), "false");
  EXPECT_EQ(Less()(Integer(3), Integer(5)).toString(), "true");
  EXPECT_EQ(Less()(Integer(3), Integer(3)).toString(), "false");
  EXPECT_EQ(Less()(Integer(3), Rational(3, 1)).toString(), "false");
  EXPECT_EQ(Less()(Rational(5, 2), Integer(2)).toString(), "false");

  EXPECT_EQ(Less()(Integer(3), Variable("a")).toString(), "-a+3<0");
  EXPECT_EQ(Less()(Variable("a"), Variable("a")).toString(), "false");

  std::unique_ptr<IOperator> o = std::make_unique<Less>();
  EXPECT_THROW((*o)(Integer(1)), FunctionCallException);
  EXPECT_THROW((*o)(Rational(2, 3)), FunctionCallException);
  EXPECT_THROW((*o)(), FunctionCallException);
  EXPECT_THROW((*o)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}

TEST(LessTests, getClassNameTest) {
  EXPECT_EQ(Less().getClassName(), "Less");
}
