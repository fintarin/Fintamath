#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Acoth;
const F f;

TEST(AcothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acoth");
}

TEST(AcothTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(AcothTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(AcothTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcothTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcothTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Inf");
  EXPECT_EQ(f(Integer(0))->toString(), "(I Pi)/2");
  EXPECT_EQ(f(Integer(1))->toString(), "Inf");
  EXPECT_EQ(f(Integer(2))->toString(), "0.5493061443340548457");

  EXPECT_EQ(f(Rational(27, 10))->toString(), "0.38885228429400418206");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "0.6404669227310321588");

  EXPECT_EQ(f(Real("1.5"))->toString(), "0.8047189562170501873");
  EXPECT_EQ(f(Real("0.5"))->toString(), "acoth(0.5)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acoth(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acoth(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcothTests, exprTest) {
  EXPECT_EQ(acothExpr(Integer(10))->toString(), "acoth(10)");
}

TEST(AcothTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Acoth, "Acoth"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Acoth, "Acoth"));
}
