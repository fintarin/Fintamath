#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/arithmetic/FracMixed.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const FracMixed f;

TEST(FracMixedTests, toStringTest) {
  EXPECT_EQ(f.toString(), "frac");
}

TEST(FracMixedTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Ternary);
}

TEST(FracMixedTests, callTest) {
  EXPECT_EQ(f(Integer(0), Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(f(Integer(0), Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(f(Integer(0), Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(f(Integer(0), Rational(-5, 2), Rational(5, 3))->toString(), "-3/2");
  EXPECT_EQ(f(Integer(2), Integer(3), Integer(5))->toString(), "13/5");
  EXPECT_EQ(f(Integer(2), Integer(3), Integer(-5))->toString(), "7/5");
  EXPECT_EQ(f(Integer(2), Integer(-3), Integer(5))->toString(), "7/5");
  EXPECT_EQ(f(Integer(-2), Integer(3), Integer(5))->toString(), "-7/5");
  EXPECT_EQ(f(Integer(-5), Integer(3), Rational(5, 2))->toString(), "-19/5");
  EXPECT_EQ(f(Integer(14), Rational(-5, 2), Integer(-3))->toString(), "89/6");
  EXPECT_EQ(f(Integer(-12), Rational(15, 5), Rational(5, -3))->toString(), "-69/5");

  EXPECT_EQ(f(Integer(0), Integer(3), Variable("a"))->toString(), "3/a");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FracMixedTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_TRUE(f.doArgsMatch({a, a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a, a}));
}

TEST(FracMixedTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, FracMixed());
  EXPECT_EQ(FracMixed(), f);
  EXPECT_EQ(f, cast<IMathObject>(FracMixed()));
  EXPECT_EQ(cast<IMathObject>(FracMixed()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(FracMixedTests, getTypeTest) {
  EXPECT_EQ(FracMixed::getTypeStatic(), MathObjectType::FracMixed);
  EXPECT_EQ(FracMixed().getType(), MathObjectType::FracMixed);
}
