#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Coth;
const F f;

TEST(CothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "coth");
}

TEST(CothTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(CothTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(CothTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(CothTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CothTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(5))->toString(), "1.0000908039820193755");
  EXPECT_EQ(f(Integer(-5))->toString(), "-1.0000908039820193755");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "10.03331113225398961");
  EXPECT_EQ(f(Rational(11, 10))->toString(), "1.2492207645683124166");

  EXPECT_EQ(f(Real("0.5"))->toString(), "2.1639534137386528488");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "coth(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "coth(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CothTests, exprTest) {
  EXPECT_EQ(cothExpr(Integer(10))->toString(), "coth(10)");
}

TEST(CothTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Coth, "Coth"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Coth, "Coth"));
}
