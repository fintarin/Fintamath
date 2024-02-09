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
  EXPECT_EQ(f(Integer(10))->toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(f(Integer(5))->toString(),
            "0.2836621854632262644666391715135573083344225922522159449303590665861514567673827");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.99500416527802576609556198780387029483857622541508403595935274468526591021824047");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "0.43298018843109500232420037773924183842996270566187693920912130535865346742072348");

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
