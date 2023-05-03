#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

using namespace fintamath;

TEST(ExpressionUtilsTests, skipBracketsTest) {
  size_t openBracketIndex = 0;
  TokenVector tokens = {"(", "a", "+", "b", "(", "a", "+", "b", "(", "a", "+", "b", ")", ")", ")", "a", "b"};

  EXPECT_TRUE(skipBrackets(tokens, openBracketIndex));
  EXPECT_FALSE(skipBrackets(tokens, openBracketIndex));

  EXPECT_EQ(openBracketIndex, 15);

  openBracketIndex = 20;
  EXPECT_FALSE(skipBrackets(tokens, openBracketIndex));
  openBracketIndex = tokens.size();
  EXPECT_FALSE(skipBrackets(tokens, openBracketIndex));

  size_t index = 0;
  EXPECT_THROW(skipBrackets(TokenVector{"(", "a"}, index), InvalidInputException);
}

TEST(ExpressionUtilsTests, cutBracketsTest) {
  TokenVector emptyTokens = {};
  TokenVector bracesTokens = {"(", "a", ")"};
  TokenVector lhsBrace = {"(", "a"};
  TokenVector rhsBrace = {"a", ")"};

  EXPECT_EQ(cutBrackets(emptyTokens), TokenVector{});
  EXPECT_EQ(cutBrackets(bracesTokens), TokenVector{"a"});
  EXPECT_EQ(cutBrackets(lhsBrace), lhsBrace);
  EXPECT_EQ(cutBrackets(rhsBrace), rhsBrace);
}

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

TEST(ExpressionUtilsTests, binaryOperatorToStringTest) {
  // TODO: implement
}

TEST(ExpressionUtilsTests, postfixUnaryOperatorToStringTest) {
  auto percent = std::make_shared<Percent>();

  EXPECT_EQ(postfixUnaryOperatorToString(*percent, std::make_shared<Integer>(-5)), "(-5)%");
  EXPECT_EQ(postfixUnaryOperatorToString(*percent, std::make_shared<Integer>(3)), "3%");
  EXPECT_EQ(postfixUnaryOperatorToString(*percent, std::make_shared<Variable>("a")), "a%");

  auto expr = Expression("(a!)!");
  EXPECT_EQ(expr.toString(), "a!!");

  expr = Expression("(a+b)!");
  EXPECT_EQ(expr.toString(), "(a + b)!");

  expr = Expression("(sin(a))!");
  EXPECT_EQ(expr.toString(), "sin(a)!");
}

TEST(ExpressionUtilsTests, prefixOperatorToStringTest) {
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

TEST(ExpressionUtilsTests, makeFunctionExpressionFromRefsVectorTest) {
  auto expr = makeFunctionExpression(Add(), {ONE, TWO});
  EXPECT_EQ(expr->toString(), "3");
  EXPECT_TRUE(is<Expression>(expr));

  Variable var("a");
  expr = makeFunctionExpression(Cos(), {var});
  EXPECT_EQ(expr->toString(), "cos(a)");
  EXPECT_TRUE(is<Expression>(expr));
}

TEST(ExpressionUtilsTests, makeFunctionExpressionFromPtrTest) {
  auto expr = makeFunctionExpression(Add(), {ONE.clone(), TWO.clone()});
  EXPECT_EQ(expr->toString(), "3");
  EXPECT_TRUE(is<INumber>(expr));

  Variable var("a");
  expr = makeFunctionExpression(Cos(), {var.clone()});
  EXPECT_EQ(expr->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr));
  EXPECT_FALSE(is<Expression>(expr));
}

TEST(ExpressionUtilsTests, makeRawFunctionExpressionTest) {
  auto expr = makeRawFunctionExpression(Add(), {ONE.clone(), TWO.clone()});
  EXPECT_EQ(expr->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr));
  EXPECT_FALSE(is<Expression>(expr));

  Variable var("a");
  expr = makeRawFunctionExpression(Cos(), {var.clone()});
  EXPECT_EQ(expr->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr));
  EXPECT_FALSE(is<Expression>(expr));
}
