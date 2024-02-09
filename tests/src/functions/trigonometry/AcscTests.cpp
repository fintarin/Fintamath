#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acsc.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acsc f;

TEST(AcscTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acsc");
}

TEST(AcscTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcscTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/2");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(-2))->toString(), "-0.52359877559829887308");
  EXPECT_EQ(f(Integer(2))->toString(), "0.52359877559829887308");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "acsc(1/10)");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "acsc(-1/5)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "acsc(0.5)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acsc(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acsc(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcscTests, exprTest) {
  EXPECT_EQ(acscExpr(Integer(10))->toString(), "acsc(10)");
}

TEST(AcscTests, getTypeTest) {
  EXPECT_EQ(Acsc::getTypeStatic(), MathObjectType::Acsc);
  EXPECT_EQ(Acsc().getType(), MathObjectType::Acsc);
}
