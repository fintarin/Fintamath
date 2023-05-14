#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/other/Percent.hpp"
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

TEST(ExpressionUtilsTests, argumentVectorToStringVectorTest) {
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

TEST(ExpressionUtilsTests, makeFunctionExpressionFromRefsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExprSimpl(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "3");
  EXPECT_TRUE(is<INumber>(expr1));

  Variable var("a");
  auto expr2 = makeExprSimpl(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
}

TEST(ExpressionUtilsTests, makeRawFunctionExpressionFromRefsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExpr(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));

  Variable var("a");
  auto expr2 = makeExpr(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
}

TEST(ExpressionUtilsTests, makeFunctionExpressionFromPtrsTest) {
  auto expr1 = makeExprSimpl(Add(), {std::make_shared<Integer>(1), std::make_shared<Integer>(2)});
  EXPECT_EQ(expr1->toString(), "3");
  EXPECT_TRUE(is<INumber>(expr1));

  auto var = std::make_shared<Variable>("a");
  auto expr2 = makeExprSimpl(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(ExpressionUtilsTests, makeRawFunctionExpressionFromPtrsTest) {
  auto expr1 = makeExpr(Add(), {std::make_shared<Integer>(1), std::make_shared<Integer>(2)});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  auto var = std::make_shared<Variable>("a");
  auto expr2 = makeExpr(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(ExpressionUtilsTests, makeFunctionExpressionFromRefsAnyArgsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExpr(Add(), one, two);
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));

  Variable var("a");
  auto expr2 = makeExpr(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
}

TEST(ExpressionUtilsTests, makeRawFunctionExpressionFromRefsAnyArgsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExprSimpl(Add(), one, two);
  EXPECT_EQ(expr1->toString(), "3");
  EXPECT_TRUE(is<INumber>(expr1));

  Variable var("a");
  auto expr2 = makeExprSimpl(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
}

TEST(ExpressionUtilsTests, makeFunctionExpressionFromPtrsArgsTest) {
  auto expr1 = makeExprSimpl(Add(), std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr1->toString(), "3");
  EXPECT_TRUE(is<INumber>(expr1));

  auto var = std::make_shared<Variable>("a");
  auto expr2 = makeExprSimpl(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(ExpressionUtilsTests, makeRawFunctionExpressionFromPtrsAnyArgsTest) {
  auto expr1 = makeExpr(Add(), std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  auto var = std::make_shared<Variable>("a");
  auto expr2 = makeExpr(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}
