#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Asec.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Asec f;

TEST(AsecTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asec");
}

TEST(AsecTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AsecTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(-2))->toString(),
            "2.0943951023931954923084289221863352561314462662500705473166297282052109375241393");
  EXPECT_EQ(f(Integer(2))->toString(),
            "1.0471975511965977461542144610931676280657231331250352736583148641026054687620697");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "asec(1/10)");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "asec(-1/5)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "asec(0.5)");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "asec(7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105)");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "asec(-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105)");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asec(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asec(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsecTests, exprTest) {
  EXPECT_EQ(asecExpr(Integer(10))->toString(), "asec(10)");
}

TEST(AsecTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AsecTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Asec());
  EXPECT_EQ(Asec(), f);
  EXPECT_EQ(f, cast<IMathObject>(Asec()));
  EXPECT_EQ(cast<IMathObject>(Asec()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AsecTests, getTypeTest) {
  EXPECT_EQ(Asec::getTypeStatic(), MathObjectType::Asec);
  EXPECT_EQ(Asec().getType(), MathObjectType::Asec);
}
