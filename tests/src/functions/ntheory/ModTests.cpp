#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/ntheory/Mod.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Mod f;

TEST(ModTests, toStringTest) {
  EXPECT_EQ(f.toString(), "mod");
}

TEST(ModTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic(), INumber::getClassStatic()));
}

TEST(ModTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(ModTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(ModTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(ModTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Modulo);
}

TEST(ModTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(ModTests, callTest) {
  EXPECT_EQ(f(Integer(0), Integer(2))->toString(), "0");
  EXPECT_EQ(f(Integer(0), Integer(-2))->toString(), "0");
  EXPECT_EQ(f(Integer(10), Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(10), Integer(-1))->toString(), "0");
  EXPECT_EQ(f(Integer(-10), Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(-10), Integer(-1))->toString(), "0");
  EXPECT_EQ(f(Integer(2), Integer(2))->toString(), "0");
  EXPECT_EQ(f(Integer(2), Integer(-2))->toString(), "0");
  EXPECT_EQ(f(Integer(-2), Integer(2))->toString(), "0");
  EXPECT_EQ(f(Integer(-2), Integer(-2))->toString(), "0");
  EXPECT_EQ(f(Integer(4), Integer(2))->toString(), "0");
  EXPECT_EQ(f(Integer(4), Integer(-2))->toString(), "0");
  EXPECT_EQ(f(Integer(4), Integer(2))->toString(), "0");
  EXPECT_EQ(f(Integer(4), Integer(-2))->toString(), "0");
  EXPECT_EQ(f(Integer(2), Integer(3))->toString(), "2");
  EXPECT_EQ(f(Integer(2), Integer(-3))->toString(), "-1");
  EXPECT_EQ(f(Integer(-2), Integer(3))->toString(), "1");
  EXPECT_EQ(f(Integer(-2), Integer(-3))->toString(), "-2");
  EXPECT_EQ(f(Integer(19), Integer(11))->toString(), "8");
  EXPECT_EQ(f(Integer(19), Integer(-11))->toString(), "-3");
  EXPECT_EQ(f(Integer(-19), Integer(11))->toString(), "3");
  EXPECT_EQ(f(Integer(-19), Integer(-11))->toString(), "-8");
  EXPECT_EQ(f(Integer(25), Integer(368273929))->toString(), "25");
  EXPECT_EQ(f(Integer(25), Integer(-368273929))->toString(), "-368273904");
  EXPECT_EQ(f(Integer(-25), Integer(368273929))->toString(), "368273904");
  EXPECT_EQ(f(Integer(-25), Integer(-368273929))->toString(), "-25");
  EXPECT_EQ(f(Integer(25), Integer(3))->toString(), "1");
  EXPECT_EQ(f(Integer(25), Integer(-3))->toString(), "-2");
  EXPECT_EQ(f(Integer(-25), Integer(3))->toString(), "2");
  EXPECT_EQ(f(Integer(-25), Integer(-3))->toString(), "-1");
  EXPECT_EQ(f(Integer(2000), Integer(36))->toString(), "20");
  EXPECT_EQ(f(Integer(2000), Integer(-36))->toString(), "-16");
  EXPECT_EQ(f(Integer(-2000), Integer(36))->toString(), "16");
  EXPECT_EQ(f(Integer(-2000), Integer(-36))->toString(), "-20");

  EXPECT_EQ(f(Rational(5, 2), Rational(2, 3))->toString(), "(5/2) mod (2/3)");

  EXPECT_EQ(f(Real("12.2"), Real("-12.2"))->toString(), "12.2 mod -12.2");

  EXPECT_EQ(f(Complex(1, 1), Complex(2, 2))->toString(), "(1 + I) mod (2 + 2 I)");

  EXPECT_EQ(f(Integer(1), Integer(0))->toString(), "Undefined");
  EXPECT_EQ(f(Rational(-1, 2), Integer(0))->toString(), "Undefined");
  EXPECT_EQ(f(Real("1.6"), Integer(0))->toString(), "Undefined");
  EXPECT_EQ(f(Complex(2, 2), Integer(0))->toString(), "Undefined");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3 mod a");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(ModTests, exprTest) {
  EXPECT_EQ(modExpr(Integer(10), Integer(10))->toString(), "10 mod 10");
}

TEST(ModTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Mod");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
