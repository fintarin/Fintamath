#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Asech.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Asech f;

TEST(AsechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asech");
}

TEST(AsechTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AsechTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AsechTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AsechTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AsechTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Inf");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(), "asech(2)");
  EXPECT_EQ(f(Integer(-2))->toString(), "asech(-2)");

  EXPECT_EQ(f(Rational(11, 10))->toString(), "asech(11/10)");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "asech(23/13)");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.3169578969248167086");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asech(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsechTests, exprTest) {
  EXPECT_EQ(asechExpr(Integer(10))->toString(), "asech(10)");
}

TEST(AsechTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Asech"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
