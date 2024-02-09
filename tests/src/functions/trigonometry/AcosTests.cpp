#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acos f;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acos");
}

TEST(AcosTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(-2))->toString(), "acos(-2)");
  EXPECT_EQ(f(Integer(2))->toString(), "acos(2)");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "1.4706289056333368229");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "1.7721542475852274107");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.0471975511965977462");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acos(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acos(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcosTests, exprTest) {
  EXPECT_EQ(acosExpr(Integer(10))->toString(), "acos(10)");
}

TEST(AcosTests, getTypeTest) {
  EXPECT_EQ(Acos::getTypeStatic(), MathObjectType::Acos);
  EXPECT_EQ(Acos().getType(), MathObjectType::Acos);
}
