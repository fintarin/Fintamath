#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(VariableTest, stringConstructorTest) {
  EXPECT_EQ(Variable("a").toString(), "a");
  EXPECT_EQ(Variable("b").toString(), "b");
  EXPECT_EQ(Variable("e").toString(), "e");
  EXPECT_EQ(Variable("i").toString(), "i");

  EXPECT_THROW(Variable("10"), InvalidInputException);
  EXPECT_THROW(Variable(""), InvalidInputException);
}

TEST(VariableTest, toStringTest) {
  EXPECT_EQ(Variable("a").toString(), "a");
  EXPECT_EQ(Variable("Z").toString(), "Z");
}
