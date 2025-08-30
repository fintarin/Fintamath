#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/core/Variable.hpp"

using namespace fintamath;

TEST(VariableTest, stringIntegerConstructorTest) {
  EXPECT_EQ(Variable("a").toString(), "a");
  EXPECT_EQ(Variable("b").toString(), "b");
  EXPECT_EQ(Variable("e").toString(), "e");

  EXPECT_EQ(Variable("a", 0).toString(), "a_0");
  EXPECT_EQ(Variable("a", 1).toString(), "a_1");
  EXPECT_EQ(Variable("a", 2).toString(), "a_2");
  EXPECT_EQ(Variable("a", Integer("100000000000000000000000000000000000000")).toString(), "a_100000000000000000000000000000000000000");

  EXPECT_THAT(
      [] { Variable(""); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("10"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "10" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("a1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "a1" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("abc"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "abc" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("1e"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "1e" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("A1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "A1" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("Bb"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "Bb" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("1C"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "1C" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("A"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "A" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("B"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "B" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("C"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "C" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "1" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "+" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "!" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("["); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "[" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("|"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "|" (expected single English lowercase letter))")));

  EXPECT_THAT(
      [] { Variable("ab", 1); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "ab" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("A", 1); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Variable name from "A" (expected single English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("a", -1); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Negative Variable index -1 is not allowed)")));
  EXPECT_THAT(
      [] { Variable("a", -2); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Negative Variable index -2 is not allowed)")));
  EXPECT_THAT(
      [] { Variable("a", Integer("-100000000000000000000000000000000000000")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Negative Variable index -100000000000000000000000000000000000000 is not allowed)")));
}

TEST(VariableTest, getClassTest) {
  EXPECT_EQ(Variable("a").getClass()->getName(), "Variable");
  EXPECT_EQ(Variable("a").getClass()->getParent(), MathObject::getClassStatic());
}
