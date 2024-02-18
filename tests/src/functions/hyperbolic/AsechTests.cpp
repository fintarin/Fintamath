#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Asech.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Asech;
const F f;

TEST(AsechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asech");
}

TEST(AsechTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(AsechTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(AsechTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AsechTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AsechTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Inf");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(), "asech(2)");
  EXPECT_EQ(f(Integer(-2))->toString(), "asech(-2)");

  EXPECT_EQ(f(Rational(11, 10))->toString(), "asech(11/10)");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "asech(23/13)");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.3169578969248167086");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asech(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsechTests, exprTest) {
  EXPECT_EQ(asechExpr(Integer(10))->toString(), "asech(10)");
}

TEST(AsechTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Asech, "Asech"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Asech, "Asech"));
}
