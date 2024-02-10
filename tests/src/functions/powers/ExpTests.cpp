#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Exp;
const F f;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(f.toString(), "exp");
}

TEST(ExpTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(ExpTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(ExpTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(ExpTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(ExpTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "E^3");
  EXPECT_EQ(f(Integer(-3))->toString(), "1/(E^3)");
  EXPECT_EQ(f(Rational(1, 3))->toString(), "root(E, 3)");

  EXPECT_EQ(f(Variable("a"))->toString(), "E^a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(ExpTests, exprTest) {
  EXPECT_EQ(expExpr(Integer(10))->toString(), "E^10");
}

TEST(ExpTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Exp);
  EXPECT_EQ(f.getType(), MathObjectType::Exp);
}
