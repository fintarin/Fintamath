#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Atan f;

TEST(AtanTests, toStringTest) {
  EXPECT_EQ(f.toString(), "atan");
}

TEST(AtanTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AtanTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AtanTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AtanTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AtanTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/4");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/4");
  EXPECT_EQ(f(Integer(-2))->toString(), "-1.107148717794090503");
  EXPECT_EQ(f(Integer(2))->toString(), "1.107148717794090503");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.099668652491162027378");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "-0.19739555984988075837");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.46364760900080611621");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "atan(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "atan(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AtanTests, exprTest) {
  EXPECT_EQ(atanExpr(Integer(10))->toString(), "atan(10)");
}

TEST(AtanTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Atan");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
