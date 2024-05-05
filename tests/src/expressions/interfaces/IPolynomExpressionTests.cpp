#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

using namespace fintamath;

const Mul f;

namespace {

class TestPolynomExpression : public IPolynomExpressionCRTP<TestPolynomExpression> {
  FINTAMATH_CLASS_BODY(TestPolynomExpression, IPolynomExpression)

public:
  explicit TestPolynomExpression(ArgumentPtrVector args) : IPolynomExpressionCRTP(f, std::move(args)) {
  }
};

FINTAMATH_CLASS_IMPLEMENTATION(TestPolynomExpression)

[[maybe_unused]] const auto config = [] {
  IPolynomExpression::registerType<TestPolynomExpression>();
  return 0;
}();

}

TEST(IPolynomExpressionTests, parseTest) {
  EXPECT_FALSE(IPolynomExpression::parseFirst("1*)"));
}

TEST(IPolynomExpressionTests, toStringTest) {
  TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});
  EXPECT_EQ(expr.toString(), "mul(1, 2, 3)");

  expr = TestPolynomExpression({addExpr(Variable("x"), Variable("y")), Variable("a").clone()});
  EXPECT_EQ(expr.toString(), "mul(x + y, a)");
}

TEST(IPolynomExpressionTests, getFunctionTest) {
  const TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IPolynomExpressionTests, getChildrenTest) {
  const TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Integer(3).clone()});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], Integer(1));
  EXPECT_EQ(*expr.getChildren()[1], Integer(2));
  EXPECT_EQ(*expr.getChildren()[2], Integer(3));
}

TEST(IPolynomExpressionTests, toMinimalObjectTest) {
  const TestPolynomExpression expr({Integer(1).clone(), Integer(2).clone(), Variable("a").clone()});
  EXPECT_EQ(expr.toMinimalObject()->toString(), "mul(a, 2)");
}

TEST(IPolynomExpressionTests, getClassTest) {
  EXPECT_EQ(IPolynomExpression::getClassStatic()->getName(), "IPolynomExpression");
  EXPECT_EQ(IPolynomExpression::getClassStatic()->getParent(), IExpression::getClassStatic());
}
