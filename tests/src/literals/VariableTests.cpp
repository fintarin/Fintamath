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
  EXPECT_EQ(Variable("a", Integer("100000000000000000000000000000000000000")).toString(),
            "a_100000000000000000000000000000000000000");

  EXPECT_THROW(Variable(""), InvalidInputException);
  EXPECT_THROW(Variable("A"), InvalidInputException);
  EXPECT_THROW(Variable("B"), InvalidInputException);
  EXPECT_THROW(Variable("C"), InvalidInputException);
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

  EXPECT_THROW(Variable("a", -1), InvalidInputException);
  EXPECT_THROW(Variable("a", -2), InvalidInputException);
  EXPECT_THROW(Variable("a", Integer("-100000000000000000000000000000000000000")), InvalidInputException);
}

TEST(VariableTest, equalsTest) {
  const Variable a("a");

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, Variable("a"));
  EXPECT_EQ(Variable("a"), a);
  EXPECT_EQ(a, cast<IMathObject>(Variable("a")));
  EXPECT_EQ(cast<IMathObject>(Variable("a")), a);
  EXPECT_NE(a, Variable("b"));
  EXPECT_NE(Variable("b"), a);
  EXPECT_NE(a, E());
  EXPECT_NE(E(), a);
}

TEST(VariableTest, getTypeTest) {
  EXPECT_EQ(Variable::getTypeStatic(), MathObjectType::Variable);
  EXPECT_EQ(Variable("a").getType(), MathObjectType::Variable);
}
