#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

using namespace fintamath;

const Mul f;

namespace {

class TestPolynomExpression final : public IPolynomExpressionCRTP<TestPolynomExpression> {
public:
  explicit TestPolynomExpression(ArgumentPtrVector args) : IPolynomExpressionCRTP(f, std::move(args)) {
  }

  static MathObjectType getTypeStatic() {
    return MathObjectBoundTypes::get().at(IPolynomExpression::getTypeStatic()) - 1;
  }
};

}

TEST(IPolynomExpressionTests, toStringTest) {
  TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});
  EXPECT_EQ(expr.toString(), "1 * 2 * 3");

  expr = TestPolynomExpression({addExpr(Variable("x"), Variable("y")), Variable("a").clone()});
  EXPECT_EQ(expr.toString(), "(x + y) * a");
}

TEST(IPolynomExpressionTests, getFunctionTest) {
  const TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IPolynomExpressionTests, getChildren) {
  const TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], Integer(1));
  EXPECT_EQ(*expr.getChildren()[1], Integer(2));
  EXPECT_EQ(*expr.getChildren()[2], Integer(3));
}

TEST(IPolynomExpressionTests, setChildren) {
  TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});

  expr.setChildren({Integer(0).clone()});
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().back(), Integer(0));

  expr.setChildren({Integer(0).clone(), Integer(0).clone()});
  EXPECT_EQ(expr.getChildren().size(), 2);
  EXPECT_EQ(*expr.getChildren().front(), Integer(0));
  EXPECT_EQ(*expr.getChildren().back(), Integer(0));

  expr.setChildren({Integer(0).clone(), Integer(0).clone(), Integer(0).clone()});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], Integer(0));
  EXPECT_EQ(*expr.getChildren()[1], Integer(0));
  EXPECT_EQ(*expr.getChildren()[2], Integer(0));

  EXPECT_THROW(expr.setChildren({}), InvalidInputFunctionException);
}

TEST(IPolynomExpressionTests, toMinimalObjectTest) {
  const TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Variable("a").clone()});
  EXPECT_EQ(expr.toMinimalObject()->toString(), "a * 2");
}

TEST(IPolynomExpressionTests, getTypeTest) {
  EXPECT_EQ(IPolynomExpression::getTypeStatic(), MathObjectType::IPolynomExpression);
}
