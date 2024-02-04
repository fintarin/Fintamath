#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Coth f;

TEST(CothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "coth");
}

TEST(CothTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CothTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(5))->toString(),
            "1.0000908039820193755366579205216876038305474375218907541594086559575724206908403");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "-1.0000908039820193755366579205216876038305474375218907541594086559575724206908403");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "10.033311132253989610145270492851499126734254107108310021176757583787897852736435");
  EXPECT_EQ(f(Rational(11, 10))->toString(),
            "1.2492207645683124165906900933942574392975063373637126905395088619158358548674384");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "2.1639534137386528487700040102180231170937386021507922725335741192960876347833395");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "coth(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "coth(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CothTests, exprTest) {
  EXPECT_EQ(cothExpr(Integer(10))->toString(), "coth(10)");
}

TEST(CothTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(CothTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Coth());
  EXPECT_EQ(Coth(), f);
  EXPECT_EQ(f, cast<IMathObject>(Coth()));
  EXPECT_EQ(cast<IMathObject>(Coth()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CothTests, getTypeTest) {
  EXPECT_EQ(Coth::getTypeStatic(), MathObjectType::Coth);
  EXPECT_EQ(Coth().getType(), MathObjectType::Coth);
}
