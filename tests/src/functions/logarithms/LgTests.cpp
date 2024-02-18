#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Lg;
const F f;

TEST(LgTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lg");
}

TEST(LgTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(LgTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(LgTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(LgTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(LgTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "1");
  EXPECT_EQ(f(Integer(20))->toString(), "1.3010299956639811952");
  EXPECT_EQ(f(Integer(2))->toString(), "0.30102999566398119521");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "-1");

  EXPECT_EQ(f(Integer(-10))->toString(), "log(10, -10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "log(10, a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LgTests, exprTest) {
  EXPECT_EQ(lgExpr(Integer(10))->toString(), "log(10, 10)");
}

TEST(LgTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Lg, "Lg"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Lg, "Lg"));
}
