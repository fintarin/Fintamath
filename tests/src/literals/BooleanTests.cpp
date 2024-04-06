#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/E.hpp"

using namespace fintamath;

TEST(BooleanTests, constructorTest) {
  EXPECT_EQ(Boolean(std::string("False")), false);
}

TEST(BooleanTests, stringConstructorTest) {
  EXPECT_EQ(Boolean("True"), true);
  EXPECT_EQ(Boolean("False"), false);

  EXPECT_THROW(Boolean("true"), InvalidInputException);
  EXPECT_THROW(Boolean("false"), InvalidInputException);
  EXPECT_THROW(Boolean("10"), InvalidInputException);
  EXPECT_THROW(Boolean("i"), InvalidInputException);
  EXPECT_THROW(Boolean(""), InvalidInputException);
  EXPECT_THROW(Boolean(""), InvalidInputException);
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
  EXPECT_EQ(Boolean().getClass()->getParent(), ILiteral::getClassStatic());
}
