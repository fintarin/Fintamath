#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Lg f;

TEST(LgTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lg");
}

TEST(LgTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(LgTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "1");
  EXPECT_EQ(f(Integer(20))->toString(),
            "1.3010299956639811952137388947244930267681898814621085413104274611271081892744245");
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.30102999566398119521373889472449302676818988146210854131042746112710818927442451");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "-1");

  EXPECT_EQ(f(Integer(-10))->toString(), "log(10, -10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "log(10, a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LgTests, exprTest) {
  EXPECT_EQ(lgExpr(Integer(10))->toString(), "log(10, 10)");
}

TEST(LgTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(LgTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Lg());
  EXPECT_EQ(Lg(), f);
  EXPECT_EQ(f, cast<IMathObject>(Lg()));
  EXPECT_EQ(cast<IMathObject>(Lg()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(LgTests, getTypeIdTest) {
  EXPECT_EQ(Lg::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Lg));
  EXPECT_EQ(Lg().getTypeId(), MathObjectTypeId(MathObjectType::Lg));
}
