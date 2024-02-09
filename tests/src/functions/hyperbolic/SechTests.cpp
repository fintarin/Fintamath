#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Sech.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sech f;

TEST(SechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sech");
}

TEST(SechTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SechTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(), "0.013475282221304557306");
  EXPECT_EQ(f(Integer(-5))->toString(), "0.013475282221304557306");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.99502074895322649163");
  EXPECT_EQ(f(Rational(11, 10))->toString(), "0.59933406057079292981");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.88681888397007390866");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sech(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SechTests, exprTest) {
  EXPECT_EQ(sechExpr(Integer(10))->toString(), "sech(10)");
}

TEST(SechTests, getTypeTest) {
  EXPECT_EQ(Sech::getTypeStatic(), MathObjectType::Sech);
  EXPECT_EQ(Sech().getType(), MathObjectType::Sech);
}
