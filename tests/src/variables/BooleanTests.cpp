#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/variables/Boolean.hpp"

using namespace fintamath;

TEST(BooleanTests, constructorTest) {
  EXPECT_EQ(Boolean("False"), false);
}

TEST(BooleanTests, stringConstructorTest) {
  EXPECT_EQ(Boolean("True"), true);
  EXPECT_EQ(Boolean("False"), false);

  EXPECT_THAT(
      [] { Boolean(std::string("")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Boolean from "" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("true")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Boolean from "true" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("false")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Boolean from "false" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("10")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Boolean from "10" (expected "True" or "False"))")));
  EXPECT_THAT(
      [] { Boolean(std::string("i")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to parse Boolean from "i" (expected "True" or "False"))")));
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

TEST(BooleanTest, getClassTest) {
  EXPECT_EQ(Boolean().getClass()->getName(), "Boolean");
  EXPECT_EQ(Boolean().getClass()->getParent(), IMathObject::getClassStatic());
}
