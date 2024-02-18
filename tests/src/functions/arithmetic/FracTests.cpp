#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Frac.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Frac;
const F f;

TEST(FracTests, toStringTest) {
  EXPECT_EQ(f.toString(), "frac");
}

TEST(FracTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IArithmetic::getTypeStatic(), IArithmetic::getTypeStatic()));
}

TEST(FracTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IArithmetic::getTypeStatic());
}

TEST(FracTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(FracTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(FracTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "3/2");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3/a");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FracTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Frac, "Frac"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Frac, "Frac"));
}
