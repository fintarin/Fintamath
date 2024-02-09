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

TEST(NequivTests, getTypeTest) {
  EXPECT_EQ(Nequiv::getTypeStatic(), MathObjectType::Nequiv);
  EXPECT_EQ(Nequiv().getType(), MathObjectType::Nequiv);
}
