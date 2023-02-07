#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Sign.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sign f;

TEST(SignTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sign");
}

TEST(SignTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SignTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "1");
  EXPECT_EQ(f(Rational(-10))->toString(), "-1");
  EXPECT_EQ(f(Real(0))->toString(), "0");

  EXPECT_EQ(f(Variable("a"))->toString(), "sign(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
