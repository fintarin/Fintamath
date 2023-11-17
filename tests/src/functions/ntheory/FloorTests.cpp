#include "gtest/gtest.h"

#include "fintamath/functions/ntheory/Floor.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Floor f;

TEST(FloorTests, toStringTest) {
  EXPECT_EQ(f.toString(), "floor");
}

TEST(FloorTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(FloorTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "-10");

  EXPECT_EQ(f(Rational("-2.9"))->toString(), "-3");
  EXPECT_EQ(f(Rational("-2.2"))->toString(), "-3");
  EXPECT_EQ(f(Rational("-2"))->toString(), "-2");
  EXPECT_EQ(f(Rational("0"))->toString(), "0");
  EXPECT_EQ(f(Rational("2"))->toString(), "2");
  EXPECT_EQ(f(Rational("2.2"))->toString(), "2");
  EXPECT_EQ(f(Rational("2.9"))->toString(), "2");

  EXPECT_EQ(f(Real("-2.9"))->toString(), "-3");
  EXPECT_EQ(f(Real("-2.2"))->toString(), "-3");
  EXPECT_EQ(f(Real("-2"))->toString(), "-3");
  EXPECT_EQ(f(Real("0"))->toString(), "0");
  EXPECT_EQ(f(Real("2"))->toString(), "2");
  EXPECT_EQ(f(Real("2.2"))->toString(), "2");
  EXPECT_EQ(f(Real("2.9"))->toString(), "2");

  EXPECT_EQ(f(Complex(0, 0))->toString(), "0");
  EXPECT_EQ(f(Complex(2, 0))->toString(), "2");
  EXPECT_EQ(f(Complex(0, 2))->toString(), "2 I");
  EXPECT_EQ(f(Complex(2, 2))->toString(), "2 + 2 I");
  EXPECT_EQ(f(Complex(Rational("1.1"), Rational("2.2")))->toString(), "1 + 2 I");
  EXPECT_EQ(f(Complex(Rational("1.1"), Rational("-2.2")))->toString(), "1 - 3 I");
  EXPECT_EQ(f(Complex(Rational("-1.1"), Rational("2.2")))->toString(), "-2 + 2 I");
  EXPECT_EQ(f(Complex(Rational("-1.1"), Rational("-2.2")))->toString(), "-2 - 3 I");
  EXPECT_EQ(f(Complex(Real("1.1"), Real("2.2")))->toString(), "1 + 2 I");
  EXPECT_EQ(f(Complex(Real("1.1"), Real("-2.2")))->toString(), "1 - 3 I");
  EXPECT_EQ(f(Complex(Real("-1.1"), Real("2.2")))->toString(), "-2 + 2 I");
  EXPECT_EQ(f(Complex(Real("-1.1"), Real("-2.2")))->toString(), "-2 - 3 I");

  EXPECT_EQ(f(Variable("a"))->toString(), "floor(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FloorTests, exprTest) {
  EXPECT_EQ(floorExpr(Integer(10))->toString(), "floor(10)");
}

TEST(FloorTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(FloorTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Floor());
  EXPECT_EQ(Floor(), f);
  EXPECT_EQ(f, cast<IMathObject>(Floor()));
  EXPECT_EQ(cast<IMathObject>(Floor()), f);
  EXPECT_NE(f, Sin());
  EXPECT_NE(Sin(), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
}

TEST(FloorTests, getTypeTest) {
  EXPECT_EQ(Floor::getTypeStatic(), MathObjectType::Floor);
  EXPECT_EQ(Floor().getType(), MathObjectType::Floor);
}
