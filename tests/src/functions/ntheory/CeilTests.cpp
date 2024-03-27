#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/ntheory/Ceil.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Ceil f;

TEST(CeilTests, toStringTest) {
  EXPECT_EQ(f.toString(), "ceil");
}

TEST(CeilTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CeilTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CeilTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(CeilTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CeilTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "-10");

  EXPECT_EQ(f(Rational("-2.9"))->toString(), "-2");
  EXPECT_EQ(f(Rational("-2.2"))->toString(), "-2");
  EXPECT_EQ(f(Rational("-2"))->toString(), "-2");
  EXPECT_EQ(f(Rational("0"))->toString(), "0");
  EXPECT_EQ(f(Rational("2"))->toString(), "2");
  EXPECT_EQ(f(Rational("2.2"))->toString(), "3");
  EXPECT_EQ(f(Rational("2.9"))->toString(), "3");

  EXPECT_EQ(f(Real("-2.9"))->toString(), "-2");
  EXPECT_EQ(f(Real("-2.2"))->toString(), "-2");
  EXPECT_EQ(f(Real("-2"))->toString(), "ceil(-2.0)");
  EXPECT_EQ(f(Real("0"))->toString(), "ceil(0.0)");
  EXPECT_EQ(f(Real("2"))->toString(), "ceil(2.0)");
  EXPECT_EQ(f(Real("2.2"))->toString(), "3");
  EXPECT_EQ(f(Real("2.9"))->toString(), "3");

  EXPECT_EQ(f(Complex(0, 0))->toString(), "0");
  EXPECT_EQ(f(Complex(2, 0))->toString(), "2");
  EXPECT_EQ(f(Complex(0, 2))->toString(), "2 I");
  EXPECT_EQ(f(Complex(2, 2))->toString(), "2 + 2 I");
  EXPECT_EQ(f(Complex(Rational("1.1"), Rational("2.2")))->toString(), "2 + 3 I");
  EXPECT_EQ(f(Complex(Rational("1.1"), Rational("-2.2")))->toString(), "2 - 2 I");
  EXPECT_EQ(f(Complex(Rational("-1.1"), Rational("2.2")))->toString(), "-1 + 3 I");
  EXPECT_EQ(f(Complex(Rational("-1.1"), Rational("-2.2")))->toString(), "-1 - 2 I");
  EXPECT_EQ(f(Complex(Real("1.1"), Real("2.2")))->toString(), "2 + 3 I");
  EXPECT_EQ(f(Complex(Real("1.1"), Real("-2.2")))->toString(), "2 - 2 I");
  EXPECT_EQ(f(Complex(Real("-1.1"), Real("2.2")))->toString(), "-1 + 3 I");
  EXPECT_EQ(f(Complex(Real("-1.1"), Real("-2.2")))->toString(), "-1 - 2 I");
  EXPECT_EQ(f(Complex(Real("0"), Real("0")))->toString(), "ceil(0.0 + 0.0 I)");
  EXPECT_EQ(f(Complex(Real("0"), Real("0.5")))->toString(), "ceil(0.0 + 0.5 I)");
  EXPECT_EQ(f(Complex(Real("0.5"), Real("0")))->toString(), "ceil(0.5 + 0.0 I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "ceil(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CeilTests, exprTest) {
  EXPECT_EQ(ceilExpr(Integer(10))->toString(), "ceil(10)");
}

TEST(CeilTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Ceil"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
