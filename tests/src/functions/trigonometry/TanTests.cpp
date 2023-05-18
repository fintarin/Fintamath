#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
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
  EXPECT_EQ(f(getPi() / 4)->toString(), "1");

  EXPECT_EQ(f(Variable("a"))->toString(), "tan(a)");

  EXPECT_THROW(f(getPi() / 2), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
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

TEST(TanTests, getTypeIdTest) {
  EXPECT_EQ(Tan::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Tan));
  EXPECT_EQ(Tan().getTypeId(), MathObjectTypeId(MathObjectType::Tan));
}
