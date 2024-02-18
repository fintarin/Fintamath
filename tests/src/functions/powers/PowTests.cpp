#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Pow;
const F f;

TEST(PowTests, toStringTest) {
  EXPECT_EQ(f.toString(), "^");
}

TEST(PowTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic(), INumber::getTypeStatic()));
}

TEST(PowTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(PowTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(PowTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(PowTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Exponentiation);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Exponentiation);
}

TEST(PowTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
  EXPECT_FALSE(f.isAssociative());
}

TEST(PowTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(0))->toString(),
            "1");
  EXPECT_EQ(f(Integer(3), Integer(2))->toString(),
            "9");
  EXPECT_EQ(f(Integer(-3), Integer(2))->toString(),
            "9");
  EXPECT_EQ(f(Integer(3), Integer(-2))->toString(),
            "1/9");
  EXPECT_EQ(f(Rational(5, 2), Integer(2))->toString(),
            "25/4");
  EXPECT_EQ(f(Integer(11), Integer(200))->toString(),
            "18990527646046182421218204639541163405858322400098778481272514561037626461679891407506620665933284558135881805238401044949435868367905913020005911442340062387227375955664576836341689587626164144676307968892001");

  EXPECT_EQ(f(Integer(0), Rational(1, 2))->toString(),
            "0");
  EXPECT_EQ(f(Integer(4), Rational(1, 2))->toString(),
            "2");
  EXPECT_EQ(f(Integer(4), Rational(1, 3))->toString(),
            "root(4, 3)");
  EXPECT_EQ(f(Integer(4), Rational(1, 4))->toString(),
            "sqrt(2)");
  EXPECT_EQ(f(Integer(8), Rational(1, 3))->toString(),
            "2");
  EXPECT_EQ(f(Integer(16), Rational(1, 4))->toString(),
            "2");
  EXPECT_EQ(f(Integer(7), Rational(1, 1000))->toString(),
            "root(7, 1000)");
  EXPECT_EQ(f(Integer(4), Rational(5, 2))->toString(),
            "32");
  EXPECT_EQ(f(Integer(4), Rational(5, 3))->toString(),
            "8 root(2, 3)");
  EXPECT_EQ(f(Integer(4), Rational(5, 4))->toString(),
            "4 sqrt(2)");
  EXPECT_EQ(f(Integer(8), Rational(5, 3))->toString(),
            "32");
  EXPECT_EQ(f(Integer(16), Rational(5, 4))->toString(),
            "32");
  EXPECT_EQ(f(Integer(7), Rational(3, 1000))->toString(),
            "root(343, 1000)");
  EXPECT_EQ(f(Integer(1), Rational(1, 1234))->toString(),
            "1");
  EXPECT_EQ(f(Integer(10000000000), Rational(1, 100))->toString(),
            "root(10, 10)");
  EXPECT_EQ(f(Integer(-4), Rational(1))->toString(),
            "-4");

  EXPECT_EQ(f(*f(Integer(10), Integer(100)), Rational(1, 100))->toString(),
            "10");
  EXPECT_EQ(f(*f(Integer(10), Integer(300)), Rational(1, 100))->toString(),
            "1000");

  EXPECT_EQ(f(Integer(4), Rational(-1, 2))->toString(),
            "1/2");
  EXPECT_EQ(f(Integer(4), Rational(-1, 3))->toString(),
            "1/root(4, 3)");
  EXPECT_EQ(f(Integer(4), Rational(-1, 4))->toString(),
            "1/sqrt(2)");
  EXPECT_EQ(f(Integer(8), Rational(-1, 3))->toString(),
            "1/2");
  EXPECT_EQ(f(Integer(16), Rational(-1, 4))->toString(),
            "1/2");
  EXPECT_EQ(f(Integer(4), Rational(-5, 2))->toString(),
            "1/32");
  EXPECT_EQ(f(Integer(4), Rational(-5, 3))->toString(),
            "1/(8 root(2, 3))");
  EXPECT_EQ(f(Integer(4), Rational(-5, 4))->toString(),
            "1/(4 sqrt(2))");
  EXPECT_EQ(f(Integer(8), Rational(-5, 3))->toString(),
            "1/32");
  EXPECT_EQ(f(Integer(16), Rational(-5, 4))->toString(),
            "1/32");
  EXPECT_EQ(f(Integer(7), Rational(-3, 1000))->toString(),
            "1/root(343, 1000)");

  EXPECT_EQ(f(Rational(-10), Rational(-3))->toString(),
            "-1/1000");
  EXPECT_EQ(f(Rational(-1), Rational(-25))->toString(),
            "-1");
  EXPECT_EQ(f(Rational("-2.2"), Rational(-5))->toString(),
            "-3125/161051");
  EXPECT_EQ(f(Rational("2.2"), Rational(-5, 2))->toString(),
            "(25 sqrt(55))/1331");

  EXPECT_EQ(f(Real("2.2"), Real("2"))->toString(),
            "4.84");
  EXPECT_EQ(f(Real("2.2"), Real("0.5"))->toString(),
            "1.4832396974191325897");

  EXPECT_EQ(f(Integer(-10), Rational(1, 2))->toString(),
            "I sqrt(10)");
  EXPECT_EQ(f(Rational(-10), Real("-1.5"))->toString(),
            "(-10)^(-1.5)"); // TODO: solve this

  EXPECT_EQ(f(Complex(1, 1), Integer(1))->toString(),
            "1 + I");
  EXPECT_EQ(f(Complex(1, 1), Rational(1, 2))->toString(),
            "sqrt(1 + I)");
  EXPECT_EQ(f(Complex(1, 1), Real("1.2"))->toString(),
            "(1 + I)^1.2");
  EXPECT_EQ(f(Complex(1, 1), Complex(1, 1))->toString(),
            "(1 + I)^(1 + I)");

  EXPECT_EQ(f(Integer(0), Integer(-1))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(-10))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(0))->toString(),
            "Undefined");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(),
            "3^a");
  EXPECT_EQ(f(Variable("a"), Rational(1, 2))->toString(),
            "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Rational(3, 2))->toString(),
            "a^(3/2)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(PowTests, exprTest) {
  EXPECT_EQ(powExpr(Integer(10), Integer(10))->toString(),
            "10^10");
}

TEST(PowTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Pow, "Pow"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Pow, "Pow"));
}
