#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Acsc.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Acsc;
const F f;

TEST(AcscTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acsc");
}

TEST(AcscTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(AcscTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(AcscTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcscTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcscTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/2");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(-2))->toString(), "-0.52359877559829887308");
  EXPECT_EQ(f(Integer(2))->toString(), "0.52359877559829887308");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "acsc(1/10)");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "acsc(-1/5)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "acsc(0.5)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acsc(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acsc(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcscTests, exprTest) {
  EXPECT_EQ(acscExpr(Integer(10))->toString(), "acsc(10)");
}

TEST(AcscTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Acsc, "Acsc"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Acsc, "Acsc"));
}
