#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Atanh f;

TEST(AtanhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "atanh");
}

TEST(AtanhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AtanhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Rational(10, 11))->toString(),
            "1.5222612188617114982502989901828527171422876437023053200970422417875370779853391");
  EXPECT_EQ(f(Rational(-10, 11))->toString(),
            "-1.5222612188617114982502989901828527171422876437023053200970422417875370779853391");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.10033534773107558063572655206003894526336286914595913587458952092779251873800939");

  EXPECT_EQ(f(Variable("a"))->toString(), "atanh(a)");

  EXPECT_THROW(f(Integer(-2)), UndefinedFunctionException);
  EXPECT_THROW(f(Integer(-1)), UndefinedFunctionException);
  EXPECT_THROW(f(Integer(1)), UndefinedFunctionException);
  EXPECT_THROW(f(Integer(2)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
