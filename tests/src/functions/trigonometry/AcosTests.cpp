#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Acos;
const F f;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acos");
}

TEST(AcosTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(AcosTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(AcosTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcosTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(-2))->toString(), "acos(-2)");
  EXPECT_EQ(f(Integer(2))->toString(), "acos(2)");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "1.4706289056333368229");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "1.7721542475852274107");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.0471975511965977462");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acos(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acos(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcosTests, exprTest) {
  EXPECT_EQ(acosExpr(Integer(10))->toString(), "acos(10)");
}

TEST(AcosTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Acos);
  EXPECT_EQ(f.getType(), MathObjectType::Acos);
}
