#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/ntheory/Floor.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Floor;
const F f;

TEST(FloorTests, toStringTest) {
  EXPECT_EQ(f.toString(), "floor");
}

TEST(FloorTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(FloorTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(FloorTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(FloorTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
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
  EXPECT_EQ(f(Real("-2"))->toString(), "floor(-2.0)");
  EXPECT_EQ(f(Real("0"))->toString(), "floor(0.0)");
  EXPECT_EQ(f(Real("2"))->toString(), "floor(2.0)");
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
  EXPECT_EQ(f(Complex(Real("0"), Real("0")))->toString(), "floor(0.0 + 0.0 I)");
  EXPECT_EQ(f(Complex(Real("0"), Real("0.5")))->toString(), "floor(0.0 + 0.5 I)");
  EXPECT_EQ(f(Complex(Real("0.5"), Real("0")))->toString(), "floor(0.5 + 0.0 I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "floor(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FloorTests, exprTest) {
  EXPECT_EQ(floorExpr(Integer(10))->toString(), "floor(10)");
}

TEST(FloorTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Floor, "Floor"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Floor, "Floor"));
}
