#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Frac.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Frac f;

TEST(FracTests, toStringTest) {
  EXPECT_EQ(f.toString(), "frac");
}

TEST(FracTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
}

TEST(FracTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(FracTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(FracTests, isEvaluatableTest) {
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

TEST(FracTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Frac");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
