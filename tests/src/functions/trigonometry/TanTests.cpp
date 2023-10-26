#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Tan f;

TEST(TanTests, toStringTest) {
  EXPECT_EQ(f.toString(), "tan");
}

TEST(TanTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(TanTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(f(Integer(-10))->toString(),
            "-0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(f(Integer(5))->toString(),
            "-3.3805150062465856369827058794473439087095692082854598771768209809183460102012061");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.10033467208545054505808004578111153681900480457644204002220806579803211288567387");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "2.081858387960084457364833448412631239447341251779062064472102733668128489376633");
  EXPECT_EQ(f(getPi() / 2)->toString(),
            "1.8284132705300082902317661058105479684239284072480833124982117000101510968883506*10^120");
  EXPECT_EQ(f(2 * getPi())->toString(),
            "-6.461329418768921910116446345071881625696223490056820540387704221111928924589791*10^-113");
  EXPECT_EQ(f(getPi() / 4)->toString(),
            "1.0");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "tan(1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "tan(-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "tan(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "tan(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(TanTests, exprTest) {
  EXPECT_EQ(tanExpr(Integer(10))->toString(), "tan(10)");
}

TEST(TanTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(TanTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Tan());
  EXPECT_EQ(Tan(), f);
  EXPECT_EQ(f, cast<IMathObject>(Tan()));
  EXPECT_EQ(cast<IMathObject>(Tan()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(TanTests, getTypeTest) {
  EXPECT_EQ(Tan::getTypeStatic(), MathObjectType::Tan);
  EXPECT_EQ(Tan().getType(), MathObjectType::Tan);
}
