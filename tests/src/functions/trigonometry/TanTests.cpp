#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

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

  EXPECT_EQ(f(Complex(1, 1))->toString(), "tan(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "tan(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(TanTests, exprTest) {
  EXPECT_EQ(tanExpr(Integer(10))->toString(), "tan(10)");
}

TEST(TanTests, getTypeTest) {
  EXPECT_EQ(Tan::getTypeStatic(), MathObjectType::Tan);
  EXPECT_EQ(Tan().getType(), MathObjectType::Tan);
}
