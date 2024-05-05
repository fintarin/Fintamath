#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionTests, constructorTest) {
  EXPECT_EQ(Expression().toString(), "0");
}

TEST(ExpressionTests, moveTest) {
  auto a = Expression("1+2");
  EXPECT_EQ(a.toString(), "3");

  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "3" && &a != &b);

  a = std::move(b);
  EXPECT_TRUE(a.toString() == "3" && &a != &b);
}

TEST(ExpressionTests, copyTest) {
  const auto a = Expression("1+2");
  const auto b = a;
  EXPECT_TRUE(a == b && &a != &b);
}

TEST(ExpressionTests, stringConstructorTest) {
  EXPECT_EQ(Expression("2").toString(), "2");
  EXPECT_EQ(Expression("2 + 2").toString(), "4");
  EXPECT_EQ(Expression(" 2 + 2 ").toString(), "4");
  EXPECT_EQ(Expression("-2 + 3").toString(), "1");
  EXPECT_EQ(Expression("sqrt144").toString(), "12");
}

TEST(ExpressionTests, stringConstructorNegativeTest) {
  EXPECT_THAT(
      [] { Expression(""); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse an expression from "" (empty input))")));
  EXPECT_THAT(
      [] { Expression("1+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse an expression from "1+" (incomplite expression with operator "+"))")));
}

TEST(ExpressionTests, getFunctionTest) {
  EXPECT_EQ(Expression().getFunction(), nullptr);
}

TEST(ExpressionTests, getChildrenTest) {
  // TODO: implement
}

TEST(ExpressionTests, setVariablesTest) {
  // TODO: implement
}

TEST(ExpressionTests, setVariableTest) {
  // Expression a("a+b+c");
  // Expression b = a;
  // Expression c = a;

  // a.setVariable(Variable("a"), 1);
  // a.setVariable(Variable("b"), 2);
  // a.setVariable(Variable("c"), 3);
  // EXPECT_EQ(a.toString(), "6");

  // b.setVariable(Variable("d"), 1);
  // EXPECT_EQ(b.toString(), "a + b + c");

  // c.setVariable(Variable("a"), Expression("ln(b)"));
  // c.setVariable(Variable("b"), Expression("E"));
  // c.setVariable(Variable("c"), Expression("(a+b)^2"));
  // EXPECT_EQ(c.toString(), "a^2 + 2 a b + b^2 + E + 1");
}

TEST(ExpressionTests, equalsTest) {
  const Expression a;

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, Expression());
  EXPECT_EQ(Expression(), a);
  EXPECT_EQ(a, cast<IMathObject>(Expression()));
  EXPECT_EQ(cast<IMathObject>(Expression()), a);
  EXPECT_NE(a, Variable("a"));
  EXPECT_NE(Variable("a"), a);

  // TODO: implement more tests
}

TEST(ExpressionTests, getClassTest) {
  EXPECT_EQ(Expression().getClass()->getName(), "Expression");
  EXPECT_EQ(Expression().getClassStatic()->getParent(), IExpression::getClassStatic());
}
