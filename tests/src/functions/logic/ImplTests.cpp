#include "gtest/gtest.h"

#include "fintamath/functions/logic/Impl.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Impl f;

TEST(ImplTests, toStringTest) {
  EXPECT_EQ(f.toString(), "->");
}

TEST(ImplTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(ImplTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Implication);
}

TEST(ImplTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "~a | b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(ImplTests, exprTest) {
  EXPECT_EQ(implExpr(Boolean(true), Boolean(false))->toString(), "~True | False");
}

TEST(ImplTests, doArgsMatchTest) {
  Boolean a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(ImplTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Impl());
  EXPECT_EQ(Impl(), f);
  EXPECT_EQ(f, cast<IMathObject>(Impl()));
  EXPECT_EQ(cast<IMathObject>(Impl()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(ImplTests, getTypeIdTest) {
  EXPECT_EQ(Impl::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Impl));
  EXPECT_EQ(Impl().getTypeId(), MathObjectTypeId(MathObjectType::Impl));
}
