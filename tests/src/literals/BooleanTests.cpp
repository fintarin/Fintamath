#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Boolean.hpp"

using namespace fintamath;

TEST(BooleanTests, stringConstructorTest) {
  EXPECT_EQ(Boolean(string("True")), true);
  EXPECT_EQ(Boolean(string("False")), false);

  EXPECT_THROW(Boolean(string("true")), InvalidInputException);
  EXPECT_THROW(Boolean(string("false")), InvalidInputException);
  EXPECT_THROW(Boolean(string("10")), InvalidInputException);
  EXPECT_THROW(Boolean(string("i")), InvalidInputException);
  EXPECT_THROW(Boolean(string("")), InvalidInputException);
  EXPECT_THROW(Boolean(string("")), InvalidInputException);
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
