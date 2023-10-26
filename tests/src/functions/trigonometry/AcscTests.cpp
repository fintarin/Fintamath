#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acsc.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Acsc f;

TEST(AcscTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acsc");
}

TEST(AcscTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcscTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/2");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(-2))->toString(),
            "-0.52359877559829887307710723054658381403286156656251763682915743205130273438103483");
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.52359877559829887307710723054658381403286156656251763682915743205130273438103483");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "acsc(1/10)");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "acsc(-1/5)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "acsc(0.5)");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "acsc(7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105)");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "acsc(-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105)");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acsc(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acsc(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcscTests, exprTest) {
  EXPECT_EQ(acscExpr(Integer(10))->toString(), "acsc(10)");
}

TEST(AcscTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AcscTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Acsc());
  EXPECT_EQ(Acsc(), f);
  EXPECT_EQ(f, cast<IMathObject>(Acsc()));
  EXPECT_EQ(cast<IMathObject>(Acsc()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AcscTests, getTypeTest) {
  EXPECT_EQ(Acsc::getTypeStatic(), MathObjectType::Acsc);
  EXPECT_EQ(Acsc().getType(), MathObjectType::Acsc);
}
