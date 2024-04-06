#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Sec.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sec f;

TEST(SecTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sec");
}

TEST(SecTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(SecTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(SecTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(SecTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SecTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(), "-1.1917935066878958109");
  EXPECT_EQ(f(Integer(5))->toString(), "3.5253200858160884067");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "1.0050209184004554285");

  EXPECT_EQ(f(Real("1.123"))->toString(), "2.3095744949058823397");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sec(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sec(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SecTests, exprTest) {
  EXPECT_EQ(secExpr(Integer(10))->toString(), "sec(10)");
}

TEST(SecTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Sec");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
