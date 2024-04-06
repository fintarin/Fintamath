#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Ln f;

TEST(LnTests, toStringTest) {
  EXPECT_EQ(f.toString(), "ln");
}

TEST(LnTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(LnTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(LnTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(LnTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(LnTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "2.302585092994045684");
  EXPECT_EQ(f(Integer(5))->toString(), "1.6094379124341003746");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "-2.302585092994045684");
  EXPECT_EQ(f(Real("2.71828"))->toString(), "0.99999932734728200316");

  EXPECT_EQ(f(Integer(-10))->toString(), "ln(-10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "ln(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(LnTests, exprTest) {
  EXPECT_EQ(lnExpr(Integer(10))->toString(), "ln(10)");
}

TEST(LnTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Ln");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
