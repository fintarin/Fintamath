#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Sinh f;

TEST(SinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sinh");
}

TEST(SinhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(),
            "74.203210577788758977009471996064565599619409004425816980661269789669690649221486");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "-74.203210577788758977009471996064565599619409004425816980661269789669690649221486");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.10016675001984402582372938352190502351492091687855888336830298619259400070170297");

  EXPECT_EQ(f(Variable("a"))->toString(), "sinh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
