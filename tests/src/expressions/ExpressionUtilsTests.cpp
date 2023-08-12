#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"

using namespace fintamath;

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

TEST(ExpressionUtilsTests, hasVariableTest) {
  auto expr = std::make_shared<Expression>("cos(sin(a))");
  EXPECT_TRUE(hasVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(sin(b))");
  EXPECT_FALSE(hasVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(a)");
  EXPECT_TRUE(hasVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(b) + a");
  EXPECT_TRUE(hasVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("cos(b)");
  EXPECT_FALSE(hasVariable(expr, Variable("a")));

  expr = std::make_shared<Expression>("10");
  EXPECT_FALSE(hasVariable(expr, Variable("a")));
}

TEST(ExpressionUtilsTests, hasVariablesTest) {
  auto expr = std::make_shared<Expression>("cos(sin(a))");
  EXPECT_TRUE(hasVariables(expr));

  expr = std::make_shared<Expression>("cos(sin(b))");
  EXPECT_TRUE(hasVariables(expr));

  expr = std::make_shared<Expression>("cos(a)");
  EXPECT_TRUE(hasVariables(expr));

  expr = std::make_shared<Expression>("cos(b)");
  EXPECT_TRUE(hasVariables(expr));

  expr = std::make_shared<Expression>("cos(2) + a");
  EXPECT_TRUE(hasVariables(expr));

  expr = std::make_shared<Expression>("10");
  EXPECT_FALSE(hasVariables(expr));
}

TEST(ExpressionUtilsTests, hasInfinityTest) {
  // TODO: implement
}
