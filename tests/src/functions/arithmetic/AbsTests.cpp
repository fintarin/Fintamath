#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Abs;
const F f;

TEST(AbsTests, toStringTest) {
  EXPECT_EQ(f.toString(), "abs");
}

TEST(AbsTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AbsTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AbsTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AbsTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AbsTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "10");
  EXPECT_EQ(f(Integer("-210"))->toString(), "210");
  EXPECT_EQ(f(Integer("4545628562"))->toString(), "4545628562");

  EXPECT_EQ(f(Rational(-5, 2))->toString(), "5/2");
  EXPECT_EQ(f(Rational(-1, 100))->toString(), "1/100");
  EXPECT_EQ(f(Rational(1, -100))->toString(), "1/100");
  EXPECT_EQ(f(Rational(10, 1000))->toString(), "1/100");

  EXPECT_EQ(f(Real("8465132.321651651"))->toString(), "8465132.321651651");
  EXPECT_EQ(f(Real("-98465136846516354684651.351"))->toString(), "9.8465136846516354685*10^22");

  EXPECT_EQ(f(Complex(2, 0))->toString(), "2");
  EXPECT_EQ(f(Complex(0, 2))->toString(), "2");
  EXPECT_EQ(f(Complex(2, 2))->toString(), "2 sqrt(2)");
  EXPECT_EQ(f(Complex(3, 2))->toString(), "sqrt(13)");
  EXPECT_EQ(f(Complex(2, 3))->toString(), "sqrt(13)");
  EXPECT_EQ(f(Complex(-2, 0))->toString(), "2");
  EXPECT_EQ(f(Complex(0, -2))->toString(), "2");
  EXPECT_EQ(f(Complex(2, -2))->toString(), "2 sqrt(2)");
  EXPECT_EQ(f(Complex(-3, 2))->toString(), "sqrt(13)");
  EXPECT_EQ(f(Complex(2, -3))->toString(), "sqrt(13)");
  EXPECT_EQ(f(Complex(-2, -3))->toString(), "sqrt(13)");

  EXPECT_EQ(f(Variable("a"))->toString(), "abs(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AbsTests, exprTest) {
  EXPECT_EQ(absExpr(Integer(10))->toString(), "abs(10)");
}

TEST(AbsTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("Abs"));
  EXPECT_EQ(F::getClassStatic().getParent(), IFunction::getClassStatic());
}
