#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Acosh;
const F f;

TEST(AcoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acosh");
}

TEST(AcoshTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AcoshTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AcoshTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcoshTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcoshTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "(I Pi)/2");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(), "1.3169578969248167086");
  EXPECT_EQ(f(Integer(-2))->toString(), "acosh(-2)");

  EXPECT_EQ(f(Rational(11, 10))->toString(), "0.44356825438511518913");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "1.1720930632462197633");

  EXPECT_EQ(f(Real("1.5"))->toString(), "0.962423650119206895");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acosh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acosh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcoshTests, exprTest) {
  EXPECT_EQ(acoshExpr(Integer(10))->toString(), "acosh(10)");
}

TEST(AcoshTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("Acosh"));
  EXPECT_EQ(F::getClassStatic().getParent(), IFunction::getClassStatic());
}
