#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Atan f;

TEST(AtanTests, toStringTest) {
  EXPECT_EQ(f.toString(), "atan");
}

TEST(AtanTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AtanTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/4");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/4");
  EXPECT_EQ(f(Integer(-2))->toString(),
            "-1.1071487177940905030170654601785370400700476454014326466765392074337103389773628");
  EXPECT_EQ(f(Integer(2))->toString(),
            "1.1071487177940905030170654601785370400700476454014326466765392074337103389773628");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "-0.19739555984988075837004976519479029344758510378785210151768894024103396997824379");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.46364760900080611621425623146121440202853705428612026381093308872019786416574171");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "atan(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "atan(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AtanTests, exprTest) {
  EXPECT_EQ(atanExpr(Integer(10))->toString(), "atan(10)");
}

TEST(AtanTests, getTypeTest) {
  EXPECT_EQ(Atan::getTypeStatic(), MathObjectType::Atan);
  EXPECT_EQ(Atan().getType(), MathObjectType::Atan);
}
