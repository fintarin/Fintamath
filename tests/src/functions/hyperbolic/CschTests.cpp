#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Csch.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Csch f;

TEST(CschTests, toStringTest) {
  EXPECT_EQ(f.toString(), "csch");
}

TEST(CschTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CschTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(5))->toString(),
            "0.013476505830589086655381881284337964618035455336483814697833142077340588519998661");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "-0.013476505830589086655381881284337964618035455336483814697833142077340588519998661");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "9.983352757296109637946884127643214807091454313327291581209572997657653557648347");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.9190347513349437194922028787270061595871798715329719464146997939789976435032901");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "csch(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "csch(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CschTests, exprTest) {
  EXPECT_EQ(cschExpr(Integer(10))->toString(), "csch(10)");
}

TEST(CschTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(CschTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Csch());
  EXPECT_EQ(Csch(), f);
  EXPECT_EQ(f, cast<IMathObject>(Csch()));
  EXPECT_EQ(cast<IMathObject>(Csch()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CschTests, getTypeTest) {
  EXPECT_EQ(Csch::getTypeStatic(), MathObjectType::Csch);
  EXPECT_EQ(Csch().getType(), MathObjectType::Csch);
}
