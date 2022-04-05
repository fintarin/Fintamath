#include <gtest/gtest.h>

#include "fintamath/variables/Variable.hpp"

using namespace fintamath;

TEST(VariableTest, stringConstructorTest){
  EXPECT_EQ(Variable("a").toString(), "a");

  EXPECT_THROW(Variable("10"), std::invalid_argument);
  EXPECT_THROW(Variable("i"), std::invalid_argument);
  EXPECT_THROW(Variable(""), std::invalid_argument);
}

TEST(VariableTest, toStringTest){
  EXPECT_EQ(Variable("a").toString(), "a");
  EXPECT_EQ(Variable("Z").toString(), "Z");
}

TEST(VariableTests, cloneTests){
  auto a = Variable("a");
  EXPECT_TRUE(&a != &(*a.clone()) && a.equals((*a.clone()).to<Variable>()));
}

TEST(VariableTests, equalsTests){
  EXPECT_TRUE(Variable("a").equals(Variable("a")));
  EXPECT_FALSE(Variable("z").equals(Variable("Z")));
}
