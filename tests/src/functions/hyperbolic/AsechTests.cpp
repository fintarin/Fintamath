#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Asech.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Asech f;

TEST(AsechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asech");
}

TEST(AsechTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AsechTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Inf");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(), "asech(2)");
  EXPECT_EQ(f(Integer(-2))->toString(), "asech(-2)");

  EXPECT_EQ(f(Rational(11, 10))->toString(), "asech(11/10)");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "asech(23/13)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.316957896924816708625046347307968444026981971467516479768472256920460185416444");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "240.48267446039699971561158991797110655024618552810197277597745092255075601329337");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "asech(-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105)");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "asech(1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "asech(-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asech(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsechTests, exprTest) {
  EXPECT_EQ(asechExpr(Integer(10))->toString(), "asech(10)");
}

TEST(AsechTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AsechTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Asech());
  EXPECT_EQ(Asech(), f);
  EXPECT_EQ(f, cast<IMathObject>(Asech()));
  EXPECT_EQ(cast<IMathObject>(Asech()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AsechTests, getTypeTest) {
  EXPECT_EQ(Asech::getTypeStatic(), MathObjectType::Asech);
  EXPECT_EQ(Asech().getType(), MathObjectType::Asech);
}
