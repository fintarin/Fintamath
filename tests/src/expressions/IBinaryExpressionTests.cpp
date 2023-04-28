#include <gtest/gtest.h>

#include "fintamath/expressions/IBinaryExpression.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

using namespace fintamath;

const Add f;

class TestBinaryExpression : public IBinaryExpressionCRTP<TestBinaryExpression> {
public:
  explicit TestBinaryExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
      : IBinaryExpressionCRTP(f, inLhsChild, inRhsChild) {
  }
};

TEST(IBinaryExpressionTests, toStringTest) {
  TestBinaryExpression expr(ONE.clone(), TWO.clone());
  EXPECT_EQ(expr.toString(), "1 + 2");
}

TEST(IBinaryExpressionTests, getFunctionTest) {
  TestBinaryExpression expr(ONE.clone(), TWO.clone());
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IBinaryExpressionTests, getChildren) {
  TestBinaryExpression expr(ONE.clone(), TWO.clone());
  EXPECT_EQ(expr.getChildren().size(), 2);
  EXPECT_EQ(*expr.getChildren().front(), ONE);
  EXPECT_EQ(*expr.getChildren().back(), TWO);
}

TEST(IBinaryExpressionTests, setChildren) {
  TestBinaryExpression expr(ONE.clone(), TWO.clone());

  expr.setChildren({ZERO.clone(), ZERO.clone()});
  EXPECT_EQ(expr.getChildren().size(), 2);
  EXPECT_EQ(*expr.getChildren().front(), ZERO);
  EXPECT_EQ(*expr.getChildren().back(), ZERO);

  EXPECT_THROW(expr.setChildren({}), InvalidInputFunctionException);
  EXPECT_THROW(expr.setChildren({ONE.clone()}), InvalidInputFunctionException);
  EXPECT_THROW(expr.setChildren({ONE.clone(), ONE.clone(), ONE.clone()}), InvalidInputFunctionException);
}
