#include <gtest/gtest.h>

#include "fintamath/expressions/IUnaryExpression.hpp"

#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

using namespace fintamath;

const Sqrt f;

class TestUnaryExpression : public IUnaryExpressionCRTP<TestUnaryExpression> {
public:
  explicit TestUnaryExpression(const ArgumentPtr &inRhsChild) : IUnaryExpressionCRTP(f, inRhsChild) {
  }
};

TEST(IUnaryExpressionTests, toStringTest) {
  TestUnaryExpression expr(ONE.clone());
  EXPECT_EQ(expr.toString(), "sqrt(1)");
}

TEST(IUnaryExpressionTests, getFunctionTest) {
  TestUnaryExpression expr(ONE.clone());
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IUnaryExpressionTests, getChildren) {
  TestUnaryExpression expr(ONE.clone());
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().front(), ONE);
}

TEST(IUnaryExpressionTests, setChildren) {
  TestUnaryExpression expr(ONE.clone());

  expr.setChildren({ZERO.clone()});
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().front(), ZERO);

  EXPECT_THROW(expr.setChildren({}), InvalidInputFunctionException);
  EXPECT_THROW(expr.setChildren({ONE.clone(), ONE.clone()}), InvalidInputFunctionException);
}
