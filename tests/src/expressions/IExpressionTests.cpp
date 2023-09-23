#include <gtest/gtest.h>

#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"

using namespace fintamath;

namespace {

class TestIExpression : public IExpressionCRTP<TestIExpression> {
public:
  std::shared_ptr<IFunction> getFunction() const override {
    return std::make_shared<Add>();
  }

  ArgumentPtrVector getChildren() const override {
    return {};
  }

  void setChildren(const ArgumentPtrVector &childVect) override {
  }

protected:
  ArgumentPtr simplify() const override {
    if (auto res = preSimplify()) {
      return res;
    }

    if (auto res = postSimplify()) {
      return res;
    }

    return clone();
  }

  ArgumentPtr preciseSimplify() const override {
    return clone();
  }
};

}

TEST(IExpressionTests, getFunctionTest) {
  // TODO: implement
}

TEST(IExpressionTests, getFunctionToStringNotationTest) {
  // TODO: implement
}

TEST(IExpressionTests, getChildrenTest) {
  // TODO: implement
}

TEST(IExpressionTests, setChildrenTest) {
  auto expr = cast<IExpression>(factorialExpr(Variable("a"))->clone());

  expr->setChildren({Variable("b").clone()});
  EXPECT_EQ(expr->toString(), "b!");

  EXPECT_THROW(expr->setChildren({Variable("b").clone(), Variable("c").clone()}), InvalidInputException);

  // TODO: implement more tests
}

TEST(IExpressionTests, getVariablesTest) {
  auto expr = cast<IExpression>(Expression("x^2+y^2+a").clone());
  auto vars = expr->getVariables();
  EXPECT_EQ(vars[0].toString(), "a");
  EXPECT_EQ(vars[1].toString(), "x");
  EXPECT_EQ(vars[2].toString(), "y");

  // TODO: implement more tests
}

TEST(IExpressionTests, setVariablesTest) {
  // TODO: implement
}

TEST(IExpressionTests, toMinimalObjectTest) {
  TestIExpression a;
  EXPECT_EQ(*a.toMinimalObject(), a);

  // TODO: implement more tests
}

TEST(IExpressionTests, equalsTest) {
  // TODO: implement
}

TEST(IExpressionTests, getTypeTest) {
  EXPECT_EQ(IExpression::getTypeStatic(), MathObjectType::IExpression);
}

TEST(IExpressionTests, arithmeticTest) {
  EXPECT_THROW(cast<IExpression>(*sinExpr(Integer(1).clone())) + cast<IExpression>(*sinExpr(Integer(1).clone())), InvalidInputException);
  EXPECT_THROW(cast<IExpression>(*sinExpr(Integer(1).clone())) - cast<IExpression>(*sinExpr(Integer(1).clone())), InvalidInputException);
  EXPECT_THROW(cast<IExpression>(*sinExpr(Integer(1).clone())) * cast<IExpression>(*sinExpr(Integer(1).clone())), InvalidInputException);
  EXPECT_THROW(cast<IExpression>(*sinExpr(Integer(1).clone())) / cast<IExpression>(*sinExpr(Integer(1).clone())), InvalidInputException);
  EXPECT_THROW(-cast<IExpression>(*sinExpr(Integer(1).clone())), InvalidInputException);
}
