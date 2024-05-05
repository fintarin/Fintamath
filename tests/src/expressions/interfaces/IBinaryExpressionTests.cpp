#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

#include "fintamath/functions/arithmetic/AddOper.hpp"

using namespace fintamath;

const AddOper f;

namespace {

class TestBinaryExpression : public IBinaryExpressionCRTP<TestBinaryExpression> {
  FINTAMATH_CLASS_BODY(TestBinaryExpression, IBinaryExpression)

public:
  explicit TestBinaryExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
      : IBinaryExpressionCRTP(f, std::move(inLhsChild), std::move(inRhsChild)) {
  }
};

FINTAMATH_CLASS_IMPLEMENTATION(TestBinaryExpression)

[[maybe_unused]] const auto config = [] {
  IBinaryExpression::registerType<TestBinaryExpression>();
  return 0;
}();

}

TEST(IBinaryExpressionTests, parseTest) {
  EXPECT_FALSE(IBinaryExpression::parseFirst("1*)"));
}

TEST(IBinaryExpressionTests, toStringTest) {
  const TestBinaryExpression expr(std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr.toString(), "1 + 2");
}

TEST(IBinaryExpressionTests, getFunctionTest) {
  const TestBinaryExpression expr(std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IBinaryExpressionTests, getChildrenTest) {
  const TestBinaryExpression expr(std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr.getChildren().size(), 2);
  EXPECT_EQ(*expr.getChildren().front(), Integer(1));
  EXPECT_EQ(*expr.getChildren().back(), Integer(2));
}

TEST(IBinaryExpressionTests, toMinimalObjectTest) {
  const TestBinaryExpression expr1(std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr1.toMinimalObject()->toString(), "3");

  const TestBinaryExpression expr2(std::make_shared<Integer>(1), Variable("a").clone());
  EXPECT_EQ(expr2.toMinimalObject()->toString(), "1 + a");
}

TEST(IBinaryExpressionTests, getClassTest) {
  EXPECT_EQ(IBinaryExpression::getClassStatic()->getName(), "IBinaryExpression");
  EXPECT_EQ(IBinaryExpression::getClassStatic()->getParent(), IExpression::getClassStatic());
}
