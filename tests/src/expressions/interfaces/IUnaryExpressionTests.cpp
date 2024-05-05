#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

#include "fintamath/functions/other/Factorial.hpp"

using namespace fintamath;

const Factorial f;

namespace {

class TestUnaryExpression : public IUnaryExpressionCRTP<TestUnaryExpression> {
  FINTAMATH_CLASS_BODY(TestUnaryExpression, IUnaryExpression)

public:
  explicit TestUnaryExpression(ArgumentPtr inRhsChild)
      : IUnaryExpressionCRTP(f, std::move(inRhsChild)) {
  }
};

FINTAMATH_CLASS_IMPLEMENTATION(TestUnaryExpression)

[[maybe_unused]] const auto config = [] {
  IUnaryExpression::registerType<TestUnaryExpression>();
  return 0;
}();

}

TEST(IUnaryExpressionTests, parseTest) {
  EXPECT_FALSE(IUnaryExpression::parseFirst("1*)"));
}

TEST(IUnaryExpressionTests, toStringTest) {
  const TestUnaryExpression expr(std::make_shared<Integer>(1));
  EXPECT_EQ(expr.toString(), "1!");
}

TEST(IUnaryExpressionTests, getFunctionTest) {
  const TestUnaryExpression expr(std::make_shared<Integer>(1));
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IUnaryExpressionTests, getChildrenTest) {
  const TestUnaryExpression expr(std::make_shared<Integer>(1));
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().front(), Integer(1));
}

TEST(IUnaryExpressionTests, toMinimalObjectTest) {
  const TestUnaryExpression expr1(Integer(4).clone());
  EXPECT_EQ(expr1.toMinimalObject()->toString(), "24");

  const TestUnaryExpression expr2(Variable("a").clone());
  EXPECT_EQ(expr2.toMinimalObject()->toString(), "a!");

  const TestUnaryExpression expr3(TestUnaryExpression(Variable("a").clone()).clone());
  EXPECT_EQ(expr3.toMinimalObject()->toString(), "(a!)!");
}

TEST(IUnaryExpressionTests, getClassTest) {
  EXPECT_EQ(IUnaryExpression::getClassStatic()->getName(), "IUnaryExpression");
  EXPECT_EQ(IUnaryExpression::getClassStatic()->getParent(), IExpression::getClassStatic());
}
