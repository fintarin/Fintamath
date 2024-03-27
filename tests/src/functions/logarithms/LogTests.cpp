#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Log f;

TEST(LogTests, toStringTest) {
  EXPECT_EQ(f.toString(), "log");
}

TEST(LogTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic(), INumber::getClassStatic()));
}

TEST(LogTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(LogTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(LogTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(LogTests, callTest) {
  EXPECT_EQ(f(Integer(10), Integer(1))->toString(),
            "0");
  EXPECT_EQ(f(Integer(0), Integer(10))->toString(),
            "0");

  EXPECT_EQ(f(Integer(10), Integer(10))->toString(),
            "1");
  EXPECT_EQ(f(Integer(10), Rational(1, 10))->toString(),
            "-1");
  EXPECT_EQ(f(Rational(1, 10), Integer(10))->toString(),
            "-1");
  EXPECT_EQ(f(Rational(1, 10), Rational(1, 10))->toString(),
            "1");

  EXPECT_EQ(f(Integer(11), Integer(11))->toString(),
            "1");
  EXPECT_EQ(f(Integer(11), Rational(1, 11))->toString(),
            "-1");
  EXPECT_EQ(f(Rational(1, 11), Integer(11))->toString(),
            "-1");
  EXPECT_EQ(f(Rational(1, 11), Rational(1, 11))->toString(),
            "1");

  EXPECT_EQ(f(Integer(10), Integer("10000000000000000000000000000000000000000000000000000000000"))->toString(),
            "58");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000000000"), Integer(10))->toString(),
            "1/58");

  EXPECT_EQ(f(Integer(121), Integer(11))->toString(),
            "1/2");
  EXPECT_EQ(f(Rational(1, 11), Integer(121))->toString(),
            "-2");
  EXPECT_EQ(f(Rational(1, 121), Integer(11))->toString(),
            "-1/2");
  EXPECT_EQ(f(Integer(121), Rational(1, 11))->toString(),
            "-1/2");
  EXPECT_EQ(f(Integer(11), Rational(1, 121))->toString(),
            "-2");

  EXPECT_EQ(f(Rational(7, 9), Rational(40353607, 387420489))->toString(),
            "9");
  EXPECT_EQ(f(Rational(40353607, 387420489), Rational(7, 9))->toString(),
            "1/9");
  EXPECT_EQ(f(Rational(387420489, 40353607), Rational(7, 9))->toString(),
            "-1/9");

  EXPECT_EQ(f(Integer(2), Integer(10))->toString(),
            "3.3219280948873623479");
  EXPECT_EQ(f(Integer(2), Integer(3))->toString(),
            "1.5849625007211561815");
  EXPECT_EQ(f(Integer(10), Real(121))->toString(),
            "2.0827853703164500815");
  EXPECT_EQ(f(Real(121), Integer(10))->toString(),
            "0.4801262838945637487");
  EXPECT_EQ(f(1 / Real(121), Integer(10))->toString(),
            "-0.4801262838945637487");
  EXPECT_EQ(f(Integer(10), 1 / Real(121))->toString(),
            "-2.0827853703164500815");

  EXPECT_EQ(f(Complex(1, 1), Complex(1, 1))->toString(),
            "1");
  EXPECT_EQ(f(Complex(1, 1), Complex(1, 2))->toString(),
            "log(1 + I, 1 + 2 I)");
  EXPECT_EQ(f(Complex(1, 1), Integer(1))->toString(),
            "0");

  EXPECT_EQ(f(Integer(10), Integer(0))->toString(),
            "-Inf");
  EXPECT_EQ(f(Rational(1, 10), Integer(0))->toString(),
            "Inf");
  EXPECT_EQ(f(Integer(1), Integer(10))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(1), Complex(1, 1))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(1), Integer(1))->toString(),
            "Undefined");
  EXPECT_EQ(f(Integer(0), Integer(0))->toString(),
            "Undefined");

  EXPECT_EQ(f(Integer(-10), Integer(10))->toString(),
            "log(-10, 10)");
  EXPECT_EQ(f(Integer(10), Integer(-10))->toString(),
            "log(10, -10)");
  EXPECT_EQ(f(Real("-10.2"), Integer(-10))->toString(),
            "log(-10.2, -10)");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(),
            "log(a, b)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LogTests, exprTest) {
  EXPECT_EQ(logExpr(Integer(10), Integer(10))->toString(),
            "log(10, 10)");
}

TEST(LogTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Log"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
