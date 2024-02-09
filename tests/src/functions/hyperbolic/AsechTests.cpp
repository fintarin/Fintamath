#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Asech.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Asech f;

TEST(AsechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asech");
}

TEST(AsechTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AsechTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Inf");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(), "asech(2)");
  EXPECT_EQ(f(Integer(-2))->toString(), "asech(-2)");

  EXPECT_EQ(f(Rational(11, 10))->toString(), "asech(11/10)");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "asech(23/13)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.316957896924816708625046347307968444026981971467516479768472256920460185416444");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asech(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsechTests, exprTest) {
  EXPECT_EQ(asechExpr(Integer(10))->toString(), "asech(10)");
}

TEST(AsechTests, getTypeTest) {
  EXPECT_EQ(Asech::getTypeStatic(), MathObjectType::Asech);
  EXPECT_EQ(Asech().getType(), MathObjectType::Asech);
}
