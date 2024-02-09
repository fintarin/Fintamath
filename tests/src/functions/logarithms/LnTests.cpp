#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Ln f;

TEST(LnTests, toStringTest) {
  EXPECT_EQ(f.toString(), "ln");
}

TEST(LnTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(LnTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "2.302585092994045684");
  EXPECT_EQ(f(Integer(5))->toString(), "1.6094379124341003746");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "-2.302585092994045684");
  EXPECT_EQ(f(getE())->toString(), "1.0");

  EXPECT_EQ(f(Integer(-10))->toString(), "ln(-10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "ln(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(LnTests, exprTest) {
  EXPECT_EQ(lnExpr(Integer(10))->toString(), "ln(10)");
}

TEST(LnTests, getTypeTest) {
  EXPECT_EQ(Ln::getTypeStatic(), MathObjectType::Ln);
  EXPECT_EQ(Ln().getType(), MathObjectType::Ln);
}
