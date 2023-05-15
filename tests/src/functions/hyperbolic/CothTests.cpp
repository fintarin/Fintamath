#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Coth f;

TEST(CothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "coth");
}

TEST(CothTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CothTests, callTest) {
  EXPECT_EQ(f(Integer(5))->toString(),
            "1.0000908039820193755366579205216876038305474375218907541594086559575724206908403");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "-1.0000908039820193755366579205216876038305474375218907541594086559575724206908403");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "10.033311132253989610145270492851499126734254107108310021176757583787897852736435");
  EXPECT_EQ(f(Rational(11, 10))->toString(),
            "1.2492207645683124165906900933942574392975063373637126905395088619158358548674384");

  EXPECT_EQ(f(Variable("a"))->toString(), "coth(a)");

  EXPECT_THROW(f(Integer(0)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
