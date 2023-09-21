#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Lb f;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lb");
}

TEST(LbTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(LbTests, callTest) {
  EXPECT_EQ(f(Integer(2))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(),
            "3.3219280948873623478703194294893901758648313930245806120547563958159347766086252");
  EXPECT_EQ(f(Integer(3))->toString(),
            "1.5849625007211561814537389439478165087598144076924810604557526545410982277943586");

  EXPECT_EQ(f(Rational(1, 16))->toString(), "-4");

  EXPECT_EQ(f(Integer(-10))->toString(), "log(2, -10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "log(2, a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LbTests, exprTest) {
  EXPECT_EQ(lbExpr(Integer(10))->toString(), "log(2, 10)");
}

TEST(LbTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(LbTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Lb());
  EXPECT_EQ(Lb(), f);
  EXPECT_EQ(f, cast<IMathObject>(Lb()));
  EXPECT_EQ(cast<IMathObject>(Lb()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(LbTests, getTypeTest) {
  EXPECT_EQ(Lb::getTypeStatic(), MathObjectType::Lb);
  EXPECT_EQ(Lb().getType(), MathObjectType::Lb);
}
