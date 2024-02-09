#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

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

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.52109530549374736162242562641149155910592898261148052794609357645280225089023359");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sinh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sinh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SinhTests, exprTest) {
  EXPECT_EQ(sinhExpr(Integer(10))->toString(), "sinh(10)");
}

TEST(SinhTests, getTypeTest) {
  EXPECT_EQ(Sinh::getTypeStatic(), MathObjectType::Sinh);
  EXPECT_EQ(Sinh().getType(), MathObjectType::Sinh);
}
