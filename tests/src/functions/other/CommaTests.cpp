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

TEST(CommaTests, doArgsMatchTest) {
  Variable a("a");
  Integer b(1);

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, b}));
  EXPECT_FALSE(f.doArgsMatch({a, b, b}));
}

TEST(CommaTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Comma());
  EXPECT_EQ(Comma(), f);
  EXPECT_EQ(f, cast<IMathObject>(Comma()));
  EXPECT_EQ(cast<IMathObject>(Comma()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CommaTests, getTypeTest) {
  EXPECT_EQ(Comma::getTypeStatic(), MathObjectType::Comma);
  EXPECT_EQ(Comma().getType(), MathObjectType::Comma);
}
