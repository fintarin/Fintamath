#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Cot f;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cot");
}

TEST(CotTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CotTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(10))->toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(f(Integer(-10))->toString(),
            "-1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(f(Integer(5))->toString(),
            "-0.29581291553274554042776716808248528606823479548153489533787776852195700157385241");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "9.9666444232592378597941126892705939076302483291514474270066809743652342102525365");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "0.48034006817334639692627931812908958751771398181244098072194466495118648453795056");
  EXPECT_EQ(f(getPi() / 2)->toString(),
            "5.4692230477529111586267970406424055872514205135096926055277982231147447746519098*10^-121");
  EXPECT_EQ(f(2 * getPi())->toString(),
            "-1.5476691175893182584480614383979923353506175302915568220959318299464914181697468*10^112");
  EXPECT_EQ(f(getPi() / 4)->toString(),
            "1.0");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "cot(1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "cot(-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cot(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cot(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CotTests, exprTest) {
  EXPECT_EQ(cotExpr(Integer(10))->toString(), "cot(10)");
}

TEST(CotTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(CotTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Cot());
  EXPECT_EQ(Cot(), f);
  EXPECT_EQ(f, cast<IMathObject>(Cot()));
  EXPECT_EQ(cast<IMathObject>(Cot()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CotTests, getTypeTest) {
  EXPECT_EQ(Cot::getTypeStatic(), MathObjectType::Cot);
  EXPECT_EQ(Cot().getType(), MathObjectType::Cot);
}
