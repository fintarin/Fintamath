#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Atanh;
const F f;

TEST(AtanhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "atanh");
}

TEST(AtanhTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(AtanhTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(AtanhTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AtanhTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AtanhTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Inf");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Inf");
  EXPECT_EQ(f(Integer(2))->toString(), "atanh(2)");

  EXPECT_EQ(f(Rational(10, 11))->toString(), "1.5222612188617114983");
  EXPECT_EQ(f(Rational(-10, 11))->toString(), "-1.5222612188617114983");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.10033534773107558064");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.5493061443340548457");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "atanh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "atanh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AtanhTests, exprTest) {
  EXPECT_EQ(atanhExpr(Integer(10))->toString(), "atanh(10)");
}

TEST(AtanhTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Atanh, "Atanh"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Atanh, "Atanh"));
}
