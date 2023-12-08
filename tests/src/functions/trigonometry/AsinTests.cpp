#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Asin f;

TEST(AsinTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asin");
}

TEST(AsinTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AsinTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/2");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(-2))->toString(), "asin(-2)");
  EXPECT_EQ(f(Integer(2))->toString(), "asin(2)");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.10016742116155979634552317945269331856867597222962954139102385503640267365086255");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "-0.20135792079033079145512555221762341024003808140222838625725124345560937462885185");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.52359877559829887307710723054658381403286156656251763682915743205130273438103483");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asin(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asin(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsinTests, exprTest) {
  EXPECT_EQ(asinExpr(Integer(10))->toString(), "asin(10)");
}

TEST(AsinTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AsinTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Asin());
  EXPECT_EQ(Asin(), f);
  EXPECT_EQ(f, cast<IMathObject>(Asin()));
  EXPECT_EQ(cast<IMathObject>(Asin()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AsinTests, getTypeTest) {
  EXPECT_EQ(Asin::getTypeStatic(), MathObjectType::Asin);
  EXPECT_EQ(Asin().getType(), MathObjectType::Asin);
}
