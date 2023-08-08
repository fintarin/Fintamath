#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
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

  EXPECT_EQ(f(Variable("a"))->toString(), "atanh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AtanhTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AtanhTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Atanh());
  EXPECT_EQ(Atanh(), f);
  EXPECT_EQ(f, cast<IMathObject>(Atanh()));
  EXPECT_EQ(cast<IMathObject>(Atanh()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AtanhTests, getTypeIdTest) {
  EXPECT_EQ(Atanh::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Atanh));
  EXPECT_EQ(Atanh().getTypeId(), MathObjectTypeId(MathObjectType::Atanh));
}
