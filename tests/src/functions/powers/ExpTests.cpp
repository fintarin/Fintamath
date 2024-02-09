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
  EXPECT_EQ(f(Integer(3))->toString(), "E^3");
  EXPECT_EQ(f(Integer(-3))->toString(), "1/(E^3)");
  EXPECT_EQ(f(Rational(1, 3))->toString(), "root(E, 3)");

  EXPECT_EQ(f(Variable("a"))->toString(), "E^a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(ExpTests, exprTest) {
  EXPECT_EQ(expExpr(Integer(10))->toString(), "E^10");
}

TEST(ExpTests, getTypeTest) {
  EXPECT_EQ(Exp::getTypeStatic(), MathObjectType::Exp);
  EXPECT_EQ(Exp().getType(), MathObjectType::Exp);
}
