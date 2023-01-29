#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(VariableTest, stringConstructorTest) {
  EXPECT_EQ(Variable("a").toString(), "a");
  EXPECT_EQ(Variable("b").toString(), "b");
  EXPECT_EQ(Variable("e").toString(), "e");
  EXPECT_EQ(Variable("A").toString(), "A");
  EXPECT_EQ(Variable("B").toString(), "B");
  EXPECT_EQ(Variable("C").toString(), "C");

  EXPECT_THROW(Variable(""), InvalidInputException);
  EXPECT_THROW(Variable("1"), InvalidInputException);
  EXPECT_THROW(Variable("+"), InvalidInputException);
  EXPECT_THROW(Variable("!"), InvalidInputException);
  EXPECT_THROW(Variable("["), InvalidInputException);
  EXPECT_THROW(Variable("|"), InvalidInputException);
  EXPECT_THROW(Variable("10"), InvalidInputException);
  EXPECT_THROW(Variable("a1"), InvalidInputException);
  EXPECT_THROW(Variable("ba"), InvalidInputException);
  EXPECT_THROW(Variable("1e"), InvalidInputException);
  EXPECT_THROW(Variable("A1"), InvalidInputException);
  EXPECT_THROW(Variable("Bb"), InvalidInputException);
  EXPECT_THROW(Variable("1C"), InvalidInputException);
}
