#include "gtest/gtest.h"

#include "fintamath/functions/logic/Nequiv.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Nequiv f;

TEST(NequivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!<->");
}

TEST(NequivTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(NequivTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Equivalence);
}

TEST(NequivTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(NequivTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "False");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "(a & ~b) | (~a & b)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(NequivTests, exprTest) {
  EXPECT_EQ(nequivExpr(Boolean(true), Boolean(false))->toString(), "(~True & False) | (True & ~False)");
}

TEST(NequivTests, doArgsMatchTest) {
  Boolean a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(NequivTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Nequiv());
  EXPECT_EQ(Nequiv(), f);
  EXPECT_EQ(f, cast<IMathObject>(Nequiv()));
  EXPECT_EQ(cast<IMathObject>(Nequiv()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(NequivTests, getTypeIdTest) {
  EXPECT_EQ(Nequiv::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Nequiv));
  EXPECT_EQ(Nequiv().getTypeId(), MathObjectTypeId(MathObjectType::Nequiv));
}
