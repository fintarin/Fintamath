#include "gtest/gtest.h"

#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Pow f;

TEST(PowTests, toStringTest) {
  EXPECT_EQ(f.toString(), "^");
}

TEST(PowTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(PowTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Exponentiation);
}

TEST(PowTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(2))->toString(), "9");
  EXPECT_EQ(f(Integer(-3), Integer(2))->toString(), "9");
  EXPECT_EQ(f(Integer(3), Integer(-2))->toString(), "1/9");
  EXPECT_EQ(f(Rational(5, 2), Integer(2))->toString(), "25/4");
  EXPECT_EQ(f(Integer(11), Integer(200))->toString(),
            "1899052764604618242121820463954116340585832240009877848127251456103762646167989140750662066593328455813588"
            "1805238401044949435868367905913020005911442340062387227375955664576836341689587626164144676307968892001");

  EXPECT_EQ(f(Integer(4), Rational(1, 2))->toString(), "2");
  EXPECT_EQ(f(Integer(4), Rational(1, 3))->toString(), "root(4, 3)");
  EXPECT_EQ(f(Integer(4), Rational(1, 4))->toString(), "sqrt(2)");
  EXPECT_EQ(f(Integer(8), Rational(1, 3))->toString(), "2");
  EXPECT_EQ(f(Integer(16), Rational(1, 4))->toString(), "2");
  EXPECT_EQ(f(Integer(7), Rational(1, 1000))->toString(), "root(7, 1000)");
  EXPECT_EQ(f(Integer(4), Rational(5, 2))->toString(), "32");
  EXPECT_EQ(f(Integer(4), Rational(5, 3))->toString(), "8 root(2, 3)");
  EXPECT_EQ(f(Integer(4), Rational(5, 4))->toString(), "4 sqrt(2)");
  EXPECT_EQ(f(Integer(8), Rational(5, 3))->toString(), "32");
  EXPECT_EQ(f(Integer(16), Rational(5, 4))->toString(), "32");
  EXPECT_EQ(f(Integer(7), Rational(3, 1000))->toString(), "root(343, 1000)");
  EXPECT_EQ(f(Integer(1), Rational(1, 1234))->toString(), "1");
  EXPECT_EQ(f(Integer(10000000000), Rational(1, 100))->toString(), "root(10, 10)");
  EXPECT_EQ(f(Integer(-4), Rational(1))->toString(), "-4");

  EXPECT_EQ(f(*f(Integer(10), Integer(100)), Rational(1, 100))->toString(), "10");
  EXPECT_EQ(f(*f(Integer(10), Integer(300)), Rational(1, 100))->toString(), "1000");

  EXPECT_EQ(f(Integer(4), Rational(-1, 2))->toString(), "1/2");
  EXPECT_EQ(f(Integer(4), Rational(-1, 3))->toString(), "1/root(4, 3)");
  EXPECT_EQ(f(Integer(4), Rational(-1, 4))->toString(), "1/sqrt(2)");
  EXPECT_EQ(f(Integer(8), Rational(-1, 3))->toString(), "1/2");
  EXPECT_EQ(f(Integer(16), Rational(-1, 4))->toString(), "1/2");
  EXPECT_EQ(f(Integer(4), Rational(-5, 2))->toString(), "1/32");
  EXPECT_EQ(f(Integer(4), Rational(-5, 3))->toString(), "1/(8 root(2, 3))");
  EXPECT_EQ(f(Integer(4), Rational(-5, 4))->toString(), "1/(4 sqrt(2))");
  EXPECT_EQ(f(Integer(8), Rational(-5, 3))->toString(), "1/32");
  EXPECT_EQ(f(Integer(16), Rational(-5, 4))->toString(), "1/32");
  EXPECT_EQ(f(Integer(7), Rational(-3, 1000))->toString(), "1/root(343, 1000)");

  EXPECT_EQ(f(Rational(-10), Rational(-3))->toString(), "-1/1000");
  EXPECT_EQ(f(Rational(-1), Rational(-25))->toString(), "-1");
  EXPECT_EQ(f(Rational("-2.2"), Rational(-5))->toString(), "-3125/161051");
  EXPECT_EQ(f(Rational("2.2"), Rational(-5, 2))->toString(), "(25 sqrt(55))/1331");

  EXPECT_EQ(f(Real("2.2"), Real("2"))->toString(), "4.84");
  EXPECT_EQ(f(Real("2.2"), Real("0.5"))->toString(),
            "1.48323969741913258974227948816014261219598086381950031974652465286876603686277");

  EXPECT_EQ(f(Rational(-10), Rational("-1.5"))->toString(), "(-10)^(-3/2)");

  EXPECT_EQ(f(Integer(0), Integer(-1))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(-10))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(0))->toString(), "Undefined");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3^a");
  EXPECT_EQ(f(Variable("a"), Rational(1, 2))->toString(), "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Rational(3, 2))->toString(), "a^(3/2)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(PowTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(PowTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Pow());
  EXPECT_EQ(Pow(), f);
  EXPECT_EQ(f, cast<IMathObject>(Pow()));
  EXPECT_EQ(cast<IMathObject>(Pow()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(PowTests, getTypeIdTest) {
  EXPECT_EQ(Pow::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Pow));
  EXPECT_EQ(Pow().getTypeId(), MathObjectTypeId(MathObjectType::Pow));
}
