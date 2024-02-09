#include "gtest/gtest.h"

#include "fintamath/functions/powers/PowFunction.hpp"

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const PowFunction f;

TEST(PowFunctionTests, toStringTest) {
  EXPECT_EQ(f.toString(), "pow");
}

TEST(PowFunctionTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(PowFunctionTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(2))->toString(), "9");
  EXPECT_EQ(f(Rational(-10), Rational(-3))->toString(), "-1/1000");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3^a");
  EXPECT_EQ(f(Variable("a"), Rational(1, 2))->toString(), "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Rational(3, 2))->toString(), "a^(3/2)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(PowFunctionTests, getTypeTest) {
  EXPECT_EQ(PowFunction::getTypeStatic(), MathObjectType::PowFunction);
  EXPECT_EQ(PowFunction().getType(), MathObjectType::PowFunction);
}
