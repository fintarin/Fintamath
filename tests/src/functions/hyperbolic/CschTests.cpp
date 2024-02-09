#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Csch.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Csch f;

TEST(CschTests, toStringTest) {
  EXPECT_EQ(f.toString(), "csch");
}

TEST(CschTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CschTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(5))->toString(), "0.013476505830589086655");
  EXPECT_EQ(f(Integer(-5))->toString(), "-0.013476505830589086655");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "9.9833527572961096379");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.9190347513349437195");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "csch(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "csch(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CschTests, exprTest) {
  EXPECT_EQ(cschExpr(Integer(10))->toString(), "csch(10)");
}

TEST(CschTests, getTypeTest) {
  EXPECT_EQ(Csch::getTypeStatic(), MathObjectType::Csch);
  EXPECT_EQ(Csch().getType(), MathObjectType::Csch);
}
