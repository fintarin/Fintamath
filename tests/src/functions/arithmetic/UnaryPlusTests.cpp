#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const UnaryPlus f;

TEST(UnaryPlusTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(UnaryPlusTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(UnaryPlusTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PrefixUnary);
}

TEST(UnaryPlusTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "3");
  EXPECT_EQ(f(Rational(5, 2))->toString(), "5/2");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "-5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");

  EXPECT_THROW(f(Integer(1), Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(UnaryPlusTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(UnaryPlusTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, UnaryPlus());
  EXPECT_EQ(UnaryPlus(), f);
  EXPECT_EQ(f, cast<IMathObject>(UnaryPlus()));
  EXPECT_EQ(cast<IMathObject>(UnaryPlus()), f);
  EXPECT_NE(f, Add());
  EXPECT_NE(Add(), f);
  EXPECT_NE(f, Neg());
  EXPECT_NE(Neg(), f);
}
