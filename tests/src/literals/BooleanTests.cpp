#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/E.hpp"

using namespace fintamath;

TEST(BooleanTests, constructorTest) {
  EXPECT_EQ(Boolean(std::string("False")), false);
}

TEST(BooleanTests, stringConstructorTest) {
  EXPECT_EQ(Boolean(std::string("True")), true);
  EXPECT_EQ(Boolean(std::string("False")), false);

  EXPECT_THAT(
      [] { Boolean(std::string("")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse a Boolean from "" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("true")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse a Boolean from "true" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("false")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse a Boolean from "false" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("10")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse a Boolean from "10" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("i")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse a Boolean from "i" (expected "True" or "False"))")));
}

TEST(BooleanTests, boolConstructorTest) {
  EXPECT_EQ(Boolean(true), true);
  EXPECT_EQ(Boolean(false), false);
}

TEST(BooleanTests, toStringTest) {
  EXPECT_EQ(Boolean(true).toString(), "True");
  EXPECT_EQ(Boolean(false).toString(), "False");
}

TEST(BooleanTests, opearatorsTest) {
  EXPECT_EQ(Boolean(false) && Boolean(false), false);
  EXPECT_EQ(Boolean(true) && Boolean(false), false);
  EXPECT_EQ(Boolean(false) && Boolean(true), false);
  EXPECT_EQ(Boolean(true) && Boolean(true), true);

  EXPECT_EQ(Boolean(false) || Boolean(false), false);
  EXPECT_EQ(Boolean(true) || Boolean(false), true);
  EXPECT_EQ(Boolean(false) || Boolean(true), true);
  EXPECT_EQ(Boolean(true) || Boolean(true), true);
}

TEST(BooleanTest, getTypeTest) {
  EXPECT_EQ(Boolean::getTypeStatic(), MathObjectType(MathObjectType::Boolean, "Boolean"));
  EXPECT_EQ(Boolean().getType(), MathObjectType(MathObjectType::Boolean, "Boolean"));
}
