#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Cosh;
const F f;

TEST(CoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cosh");
}

TEST(CoshTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CoshTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CoshTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(CoshTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CoshTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(), "74.209948524787844444");
  EXPECT_EQ(f(Integer(-5))->toString(), "74.209948524787844444");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "1.005004168055803599");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.1276259652063807852");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cosh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cosh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CoshTests, exprTest) {
  EXPECT_EQ(coshExpr(Integer(10))->toString(), "cosh(10)");
}

TEST(CoshTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("Cosh"));
  EXPECT_EQ(F::getClassStatic().getParent(), IFunction::getClassStatic());
}
