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

TEST(ExpTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(ExpTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
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

TEST(ExpTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("Exp"));
  EXPECT_EQ(F::getClassStatic().getParent(), IFunction::getClassStatic());
}
