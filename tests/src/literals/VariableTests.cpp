#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"

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
          testing::StrEq(R"(Invalid Variable "" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("10"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "10" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("a1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "a1" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("abc"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "abc" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("1e"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "1e" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("A1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "A1" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("Bb"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "Bb" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("1C"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "1C" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("A"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "A" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("B"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "B" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("C"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "C" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "1" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "+" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "!" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("["); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "[" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("|"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "|" (name expected to be an English lowercase letter))")));

  EXPECT_THAT(
      [] { Variable("A", 1); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "A" (name expected to be an English lowercase letter))")));
  EXPECT_THAT(
      [] { Variable("ab", 1); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "ab" (name expected to be 1 character))")));
  EXPECT_THAT(
      [] { Variable("a", -1); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "a_-1" (expected index >= 0))")));
  EXPECT_THAT(
      [] { Variable("a", -2); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "a_-2" (expected index >= 0))")));
  EXPECT_THAT(
      [] { Variable("a", Integer("-100000000000000000000000000000000000000")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid Variable "a_-100000000000000000000000000000000000000" (expected index >= 0))")));
}

TEST(VariableTest, getTypeTest) {
  EXPECT_EQ(Variable::getTypeStatic(), MathObjectType(MathObjectType::Variable, "Variable"));
  EXPECT_EQ(Variable("a").getType(), MathObjectType(MathObjectType::Variable, "Variable"));
}
