#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Add f;

TEST(AddTests, toStringTest) {
  EXPECT_EQ(f.toString(), "add");
}

TEST(AddTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
}

TEST(AddTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(AddTests, isVariadicTest) {
  EXPECT_TRUE(f.isVariadic());
}

TEST(AddTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AddTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Rational(1, 2))->toString(), "1/2");
  EXPECT_EQ(f(Real("0.333"))->toString(), "0.333");
  EXPECT_EQ(f(Complex(1, 2))->toString(), "1 + 2 I");
  EXPECT_EQ(f(Integer(13), Integer(56))->toString(), "69");
  EXPECT_EQ(f(Integer(33), Rational(4, 3))->toString(), "103/3");
  EXPECT_EQ(f(Rational(1, 2), Integer(10))->toString(), "21/2");
  EXPECT_EQ(f(Rational(1, 2), Rational(7, 2))->toString(), "4");
  EXPECT_EQ(f(Rational(1, 2), Rational(7, 3))->toString(), "17/6");
  EXPECT_EQ(f(Integer(1), Integer(1), Integer(1))->toString(), "3");
  EXPECT_EQ(f(Integer(1), Rational(1, 2), Integer(1), Real("0.5"))->toString(), "3.0");
  EXPECT_EQ(f(Complex(1, 2), Complex(Real(2), Rational(3, 2)), Rational(1, 2), Integer(1), Real("0.6"))->toString(), "5.1 + 7/2 I");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "a + 5");
  EXPECT_EQ(f(Variable("a"), Variable("a"), Variable("b"))->toString(), "2 a + b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
}

TEST(AddTests, exprTest) {
  EXPECT_EQ(addExpr(Integer(10), Integer(10))->toString(), "10 + 10");
}

TEST(AddTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Add"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
