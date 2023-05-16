#include "gtest/gtest.h"

#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Exp f;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(f.toString(), "exp");
}

TEST(ExpTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(ExpTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(),
            "20.085536923187667740928529654581717896987907838554150144378934229698845878091974");
  EXPECT_EQ(f(Integer(3))->toString(),
            "20.085536923187667740928529654581717896987907838554150144378934229698845878091974");
  EXPECT_EQ(f(Integer(-3))->toString(),
            "0.04978706836786394297934241565006177663169959218842321556762772760606066773019955");
  EXPECT_EQ(f(Rational(1, 3))->toString(),
            "1.3956124250860895286281253196025868375979065151994069826175167060317390156459518");

  EXPECT_EQ(f(Variable("a"))->toString(), "E^a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(ExpTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(ExpTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Exp());
  EXPECT_EQ(Exp(), f);
  EXPECT_EQ(f, cast<IMathObject>(Exp()));
  EXPECT_EQ(cast<IMathObject>(Exp()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}
