#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Cos f;

TEST(CosTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cos");
}

TEST(CosTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CosTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(), "-0.83907152907645245226");
  EXPECT_EQ(f(Integer(5))->toString(), "0.28366218546322626447");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.9950041652780257661");

  EXPECT_EQ(f(Real("1.123"))->toString(), "0.43298018843109500232");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cos(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cos(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CosTests, exprTest) {
  EXPECT_EQ(cosExpr(Integer(10))->toString(), "cos(10)");
}

TEST(CosTests, getTypeTest) {
  EXPECT_EQ(Cos::getTypeStatic(), MathObjectType::Cos);
  EXPECT_EQ(Cos().getType(), MathObjectType::Cos);
}
