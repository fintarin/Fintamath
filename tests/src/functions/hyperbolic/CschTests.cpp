#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Csch.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Csch;
const F f;

TEST(CschTests, toStringTest) {
  EXPECT_EQ(f.toString(), "csch");
}

TEST(CschTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CschTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CschTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(CschTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CschTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(5))->toString(), "0.013476505830589086655");
  EXPECT_EQ(f(Integer(-5))->toString(), "-0.013476505830589086655");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "9.9833527572961096379");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.9190347513349437195");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "csch(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "csch(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CschTests, exprTest) {
  EXPECT_EQ(cschExpr(Integer(10))->toString(), "csch(10)");
}

TEST(CschTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("Csch"));
  EXPECT_EQ(F::getClassStatic().getParent(), IFunction::getClassStatic());
}
