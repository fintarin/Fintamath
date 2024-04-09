#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Exp f;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(f.toString(), "exp");
}

TEST(ExpTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(ExpTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(ExpTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(ExpTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(ExpTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "E^3");
  EXPECT_EQ(f(Integer(-3))->toString(), "1/(E^3)");
  EXPECT_EQ(f(Rational(1, 3))->toString(), "root(E, 3)");

  EXPECT_EQ(f(Variable("a"))->toString(), "E^a");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Exp "exp" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Exp "exp" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Exp "exp" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Exp "exp" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Exp "exp" with 4 arguments (expected 1))")));
}

TEST(ExpTests, exprTest) {
  EXPECT_EQ(expExpr(Integer(10))->toString(), "E^10");
}

TEST(ExpTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Exp");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
