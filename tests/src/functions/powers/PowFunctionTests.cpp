#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/PowFunction.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = PowFunction;
const F f;

TEST(PowFunctionTests, toStringTest) {
  EXPECT_EQ(f.toString(), "pow");
}

TEST(PowFunctionTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IArithmetic::getTypeStatic(), IArithmetic::getTypeStatic()));
}

TEST(PowFunctionTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IArithmetic::getTypeStatic());
}

TEST(PowFunctionTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(PowFunctionTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(PowFunctionTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(2))->toString(), "9");
  EXPECT_EQ(f(Rational(-10), Rational(-3))->toString(), "-1/1000");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3^a");
  EXPECT_EQ(f(Variable("a"), Rational(1, 2))->toString(), "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Rational(3, 2))->toString(), "a^(3/2)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(PowFunctionTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::PowFunction, "PowFunction"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::PowFunction, "PowFunction"));
}
