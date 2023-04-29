#include <gtest/gtest.h>

#include "fintamath/expressions/IPolynomExpression.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

using namespace fintamath;

const Add f;

class TestPolynomExpression : public IPolynomExpressionCRTP<TestPolynomExpression> {
public:
  explicit TestPolynomExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(f, children) {
  }

protected:
  std::string childToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override {
    return (prevChild ? " " + func->toString() + " " : "") + inChild->toString();
  }
};

TEST(IPolynomExpressionTests, toStringTest) {
  TestPolynomExpression expr({ONE.clone(), TWO.clone(), THREE.clone()});
  EXPECT_EQ(expr.toString(), "1 + 2 + 3");
}

TEST(IPolynomExpressionTests, getFunctionTest) {
  TestPolynomExpression expr({ONE.clone(), TWO.clone(), THREE.clone()});
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IPolynomExpressionTests, getChildren) {
  TestPolynomExpression expr({ONE.clone(), TWO.clone(), THREE.clone()});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], ONE);
  EXPECT_EQ(*expr.getChildren()[1], TWO);
  EXPECT_EQ(*expr.getChildren()[2], THREE);
}

TEST(IPolynomExpressionTests, setChildren) {
  TestPolynomExpression expr({ONE.clone(), TWO.clone(), THREE.clone()});

  expr.setChildren({ZERO.clone()});
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().back(), ZERO);

  expr.setChildren({ZERO.clone(), ZERO.clone()});
  EXPECT_EQ(expr.getChildren().size(), 2);
  EXPECT_EQ(*expr.getChildren().front(), ZERO);
  EXPECT_EQ(*expr.getChildren().back(), ZERO);

  expr.setChildren({ZERO.clone(), ZERO.clone(), ZERO.clone()});
  EXPECT_EQ(expr.getChildren().size(), 3);
  EXPECT_EQ(*expr.getChildren()[0], ZERO);
  EXPECT_EQ(*expr.getChildren()[1], ZERO);
  EXPECT_EQ(*expr.getChildren()[2], ZERO);

  EXPECT_THROW(expr.setChildren({}), InvalidInputFunctionException);
}

TEST(IPolynomExpressionTests, addElement) {
  TestPolynomExpression expr({ONE.clone(), TWO.clone(), THREE.clone()});
  expr.addElement(ZERO.clone());
  EXPECT_EQ(expr.toString(), "1 + 2 + 3 + 0");
}
