#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Tan f;

TEST(TanTests, toStringTest) {
  EXPECT_EQ(f.toString(), "tan");
}

TEST(TanTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(TanTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(TanTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(TanTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(TanTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "0.64836082745908667126");
  EXPECT_EQ(f(Integer(-10))->toString(), "-0.64836082745908667126");
  EXPECT_EQ(f(Integer(5))->toString(), "-3.380515006246585637");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.10033467208545054506");

  EXPECT_EQ(f(Real("1.123"))->toString(), "2.0818583879600844574");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "tan(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "tan(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(TanTests, exprTest) {
  EXPECT_EQ(tanExpr(Integer(10))->toString(), "tan(10)");
}

TEST(TanTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Tan"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
