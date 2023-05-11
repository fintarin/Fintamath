#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"

using namespace fintamath;

const Add f;

class TestPolynomExpression : public IPolynomExpressionCRTP<TestPolynomExpression> {
public:
  explicit TestPolynomExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(f, children) {
  }

protected:
  std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override {
    return (prevChild ? " " + func->toString() + " " : "") + inChild->toString();
  }
};

TEST(IPolynomExpressionTests, toStringTest) {
  TestPolynomExpression expr({std::make_shared<Integer>(1), std::make_shared<Integer>(2), std::make_shared<Integer>(3)});
  EXPECT_EQ(expr.toString(), "1 + 2 + 3");
}

TEST(IPolynomExpressionTests, getFunctionTest) {
  TestPolynomExpression expr({std::make_shared<Integer>(1), std::make_shared<Integer>(2), std::make_shared<Integer>(3)});
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IPolynomExpressionTests, getChildren) {
  TestPolynomExpression expr({std::make_shared<Integer>(1), std::make_shared<Integer>(2), std::make_shared<Integer>(3)});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], Integer(1));
  EXPECT_EQ(*expr.getChildren()[1], Integer(2));
  EXPECT_EQ(*expr.getChildren()[2], Integer(3));
}

TEST(IPolynomExpressionTests, setChildren) {
  TestPolynomExpression expr({std::make_shared<Integer>(1), std::make_shared<Integer>(2), std::make_shared<Integer>(3)});

  expr.setChildren({std::make_shared<Integer>(0)});
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().back(), Integer(0));

  expr.setChildren({std::make_shared<Integer>(0), std::make_shared<Integer>(0)});
  EXPECT_EQ(expr.getChildren().size(), 2);
  EXPECT_EQ(*expr.getChildren().front(), Integer(0));
  EXPECT_EQ(*expr.getChildren().back(), Integer(0));

  expr.setChildren({std::make_shared<Integer>(0), std::make_shared<Integer>(0), std::make_shared<Integer>(0)});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], Integer(0));
  EXPECT_EQ(*expr.getChildren()[1], Integer(0));
  EXPECT_EQ(*expr.getChildren()[2], Integer(0));

  EXPECT_THROW(expr.setChildren({}), InvalidInputFunctionException);
}

TEST(IPolynomExpressionTests, addElement) {
  TestPolynomExpression expr({std::make_shared<Integer>(1), std::make_shared<Integer>(2), std::make_shared<Integer>(3)});
  expr.addElement(std::make_shared<Integer>(0));
  EXPECT_EQ(expr.toString(), "1 + 2 + 3 + 0");
}

TEST(IPolynomExpressionTests, toMinimalObjectTest) {
  TestPolynomExpression expr({std::make_shared<Integer>(1), std::make_shared<Integer>(2), Variable("a").clone()});
  EXPECT_EQ(expr.toMinimalObject()->toString(), "a + 3");
}
