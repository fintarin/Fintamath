#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(SignExprTests, getClassTest) {
  const auto expr = signExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass()->getName(), "SignExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IUnaryExpression::getClassStatic());
}
