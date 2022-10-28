#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(VariableTest, stringConstructorTest) {
  EXPECT_EQ(Variable("a").toString(), "a");

  EXPECT_THROW(Variable("10"), InvalidInputException);
  EXPECT_THROW(Variable("i"), InvalidInputException);
  EXPECT_THROW(Variable(""), InvalidInputException);
}

TEST(VariableTest, toStringTest) {
  EXPECT_EQ(Variable("a").toString(), "a");
  EXPECT_EQ(Variable("Z").toString(), "Z");
}
