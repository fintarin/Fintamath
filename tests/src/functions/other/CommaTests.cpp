#include "gtest/gtest.h"

#include "fintamath/functions/other/Comma.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

const Comma f;

TEST(CommaTests, toStringTest) {
  EXPECT_EQ(f.toString(), ",");
}

TEST(CommaTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(CommaTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Comma);
}

TEST(CommaTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(CommaTests, callTest) {
  EXPECT_THROW(f(Variable("a"), Variable("a"))->toString(), InvalidInputException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CommaTests, exprTest) {
  EXPECT_EQ(commaExpr(Variable("a"), Integer(1))->toString(), "a , 1");
}

TEST(CommaTests, getTypeTest) {
  EXPECT_EQ(Comma::getTypeStatic(), MathObjectType::Comma);
  EXPECT_EQ(Comma().getType(), MathObjectType::Comma);
}
