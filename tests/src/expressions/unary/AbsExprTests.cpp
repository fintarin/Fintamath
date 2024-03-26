#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(AbsExprTests, getClassTest) {
  EXPECT_EQ(absExpr(Integer(0).clone())->getClass(), MathObjectClass("AbsExpr"));
}
