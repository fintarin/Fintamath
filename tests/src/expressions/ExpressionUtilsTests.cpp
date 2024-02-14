#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;
using namespace detail;

TEST(ExpressionUtilsTests, putInBracketsTest) {
  EXPECT_EQ(putInBrackets(""), "()");
  EXPECT_EQ(putInBrackets("a"), "(a)");
  EXPECT_EQ(putInBrackets("ab"), "(ab)");
}

TEST(ExpressionUtilsTests, putInSpacesTest) {
  EXPECT_EQ(putInSpaces(""), "  ");
  EXPECT_EQ(putInSpaces("a"), " a ");
  EXPECT_EQ(putInSpaces("ab"), " ab ");
}

TEST(ExpressionUtilsTests, functionToStringTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, binaryOperatorToStringTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, prefixOperatorToStringTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, postfixUnaryOperatorToStringTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, argumentVectorToStringVectorTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, argumentRefVectorToArgumentPtrVector) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, containsIfTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, containsChildTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, containsVariableTest) {
  EXPECT_TRUE(containsVariable(Variable("a").clone(), Variable("a")));

  EXPECT_FALSE(containsVariable(Variable("b").clone(), Variable("a")));

  EXPECT_FALSE(containsVariable(Integer(1).clone(), Variable("a")));

  auto expr = std::make_shared<Expression>("cos(sin(a))");
  EXPECT_TRUE(containsVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(sin(b))");
  EXPECT_FALSE(containsVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(a)");
  EXPECT_TRUE(containsVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(b) + a");
  EXPECT_TRUE(containsVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(b)");
  EXPECT_FALSE(containsVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("10");
  EXPECT_FALSE(containsVariable(expr, Variable("a")));
}

TEST(ExpressionUtilsTests, containsVariablesTest) {
  EXPECT_TRUE(containsVariable(Variable("a").clone()));

  EXPECT_FALSE(containsVariable(Integer(1).clone()));

  auto expr = std::make_shared<Expression>("cos(sin(a))");
  EXPECT_TRUE(containsVariable(expr));

  expr = std::make_shared<Expression>("cos(sin(b))");
  EXPECT_TRUE(containsVariable(expr));

  expr = std::make_shared<Expression>("cos(a)");
  EXPECT_TRUE(containsVariable(expr));

  expr = std::make_shared<Expression>("cos(b)");
  EXPECT_TRUE(containsVariable(expr));

  expr = std::make_shared<Expression>("cos(2) + a");
  EXPECT_TRUE(containsVariable(expr));

  expr = std::make_shared<Expression>("10");
  EXPECT_FALSE(containsVariable(expr));
}

TEST(ExpressionUtilsTests, constainsInfinityTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, containsComplexTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, isInfinityTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, isNegatedExpressionTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, isNegativeNumberTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, makePolynomTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, negateTest) {
  // TODO: implement
}
