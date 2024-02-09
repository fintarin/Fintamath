#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Atanh f;

TEST(AtanhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "atanh");
}

TEST(AtanhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AtanhTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Inf");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Inf");
  EXPECT_EQ(f(Integer(2))->toString(), "atanh(2)");

  EXPECT_EQ(f(Rational(10, 11))->toString(),
            "1.5222612188617114982502989901828527171422876437023053200970422417875370779853391");
  EXPECT_EQ(f(Rational(-10, 11))->toString(),
            "-1.5222612188617114982502989901828527171422876437023053200970422417875370779853391");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.10033534773107558063572655206003894526336286914595913587458952092779251873800939");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.54930614433405484569762261846126285232374527891137472586734716681874714660930448");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "atanh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "atanh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AtanhTests, exprTest) {
  EXPECT_EQ(atanhExpr(Integer(10))->toString(), "atanh(10)");
}

TEST(AtanhTests, getTypeTest) {
  EXPECT_EQ(Atanh::getTypeStatic(), MathObjectType::Atanh);
  EXPECT_EQ(Atanh().getType(), MathObjectType::Atanh);
}
