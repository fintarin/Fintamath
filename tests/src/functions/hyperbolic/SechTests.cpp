#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Sech.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Sech f;

TEST(SechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sech");
}

TEST(SechTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SechTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(),
            "0.013475282221304557305519138244882155290837353941700686833281903496663283728530963");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "0.013475282221304557305519138244882155290837353941700686833281903496663283728530963");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.99502074895322649163450651259973258837543977179588911806474392458135689767658403");
  EXPECT_EQ(f(Rational(11, 10))->toString(),
            "0.59933406057079292980967297416884494701348664448571290570839777151293711061462317");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.88681888397007390865889779778340856253408908871261392483625888256169427121000406");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sech(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SechTests, exprTest) {
  EXPECT_EQ(sechExpr(Integer(10))->toString(), "sech(10)");
}

TEST(SechTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SechTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sech());
  EXPECT_EQ(Sech(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sech()));
  EXPECT_EQ(cast<IMathObject>(Sech()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SechTests, getTypeTest) {
  EXPECT_EQ(Sech::getTypeStatic(), MathObjectType::Sech);
  EXPECT_EQ(Sech().getType(), MathObjectType::Sech);
}
