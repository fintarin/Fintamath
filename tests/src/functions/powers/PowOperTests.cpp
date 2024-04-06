#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/PowOper.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const PowOper f;

TEST(PowOperTests, toStringTest) {
  EXPECT_EQ(f.toString(), "^");
}

TEST(PowOperTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic(), INumber::getClassStatic()));
}

TEST(PowOperTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(PowOperTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(PowOperTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(PowOperTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Exponentiation);
}

TEST(PowOperTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(PowOperTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(2))->toString(), "9");
  EXPECT_EQ(f(Rational(-10), Rational(-3))->toString(), "-1/1000");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3^a");
  EXPECT_EQ(f(Variable("a"), Rational(1, 2))->toString(), "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Rational(3, 2))->toString(), "a^(3/2)");

  EXPECT_THROW(f(), InvalidInputException);
  EXPECT_THROW(f(Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputException);
}

TEST(PowOperTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("PowOper"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
