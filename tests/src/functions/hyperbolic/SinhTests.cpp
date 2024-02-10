#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Sinh;
const F f;

TEST(SinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sinh");
}

TEST(SinhTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(SinhTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(SinhTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(SinhTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(), "74.203210577788758977");
  EXPECT_EQ(f(Integer(-5))->toString(), "-74.203210577788758977");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.10016675001984402582");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.52109530549374736162");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sinh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sinh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SinhTests, exprTest) {
  EXPECT_EQ(sinhExpr(Integer(10))->toString(), "sinh(10)");
}

TEST(SinhTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Sinh);
  EXPECT_EQ(f.getType(), MathObjectType::Sinh);
}
