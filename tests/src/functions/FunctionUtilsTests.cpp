#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/MulOper.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/PowOper.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace detail;

TEST(FunctionUtilsTests, makeExprWithValidationPtrsTest) {
  ArgumentPtr one = std::make_unique<Integer>(1);
  ArgumentPtr two = std::make_unique<Integer>(2);
  auto expr1 = makeExprWithValidation(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_FALSE(is<INumber>(expr1));

  ArgumentPtr var = std::make_unique<Variable>("a");
  ArgumentPtr expr2 = makeExprWithValidation(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));

  EXPECT_THAT(
      [&] { makeExprWithValidation(MulOper(), ArgumentPtrVector{var}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call MulOper "*" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [] { makeExprWithValidation(MulOper(), ArgumentPtrVector{}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call MulOper "*" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { makeExprWithValidation(PowOper(), ArgumentPtrVector{var}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call PowOper "^" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [] { makeExprWithValidation(PowOper(), ArgumentPtrVector{}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call PowOper "^" with 0 arguments (expected 2))")));
}

TEST(FunctionUtilsTests, makeExprWithValidationRefsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExprWithValidation(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_FALSE(is<INumber>(expr1));

  Variable var("a");
  auto expr2 = makeExprWithValidation(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));

  EXPECT_THAT(
      [&] { makeExprWithValidation(MulOper(), ArgumentRefVector{var}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call MulOper "*" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [] { makeExprWithValidation(MulOper(), ArgumentRefVector{}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call MulOper "*" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { makeExprWithValidation(PowOper(), ArgumentRefVector{var}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call PowOper "^" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [] { makeExprWithValidation(PowOper(), ArgumentRefVector{}); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call PowOper "^" with 0 arguments (expected 2))")));
}

TEST(FunctionUtilsTests, makeExprWithValidationAnyArgsRefTest) {
  const auto expr1 = makeExprWithValidation(Add(), Integer(1), Integer(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  const auto var = Variable("a");
  const auto expr2 = makeExprWithValidation(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(FunctionUtilsTests, makeExprWithValidationAnyArgsPtrTest) {
  const auto expr1 = makeExprWithValidation(Add(), std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  auto var = std::make_shared<Variable>("a");
  const auto expr2 = makeExprWithValidation(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(FunctionUtilsTests, makeExprPtrsTest) {
  ArgumentPtr one = std::make_unique<Integer>(1);
  ArgumentPtr two = std::make_unique<Integer>(2);
  auto expr1 = makeExpr(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_FALSE(is<INumber>(expr1));

  ArgumentPtr var = std::make_unique<Variable>("a");
  ArgumentPtr expr2 = makeExpr(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
}

TEST(FunctionUtilsTests, makeExprRefsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExpr(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_FALSE(is<INumber>(expr1));

  Variable var("a");
  auto expr2 = makeExpr(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
}

TEST(FunctionUtilsTests, makeExprAnyArgsRefTest) {
  const auto expr1 = makeExpr(Add(), Integer(1), Integer(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  const auto var = Variable("a");
  const auto expr2 = makeExpr(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(FunctionUtilsTests, makeExprAnyArgsPtrTest) {
  const auto expr1 = makeExpr(Add(), std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  auto var = std::make_shared<Variable>("a");
  const auto expr2 = makeExpr(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(FunctionUtilsTests, argumentRefVectorToArgumentPtrVectorTest) {
  // TODO: implement
}
