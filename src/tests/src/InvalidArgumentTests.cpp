#include <gtest/gtest.h>

#include <stdexcept>

#include "expressions/Expression.hpp"
#include "single_entities/operators/Function.hpp"
#include "single_entities/operators/Operator.hpp"
#include "single_entities/terms/literals/Constant.hpp"
#include "single_entities/terms/numbers/Integer.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

TEST(InvalidArgumentTests, functionTest) {
  EXPECT_THROW(Function("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, operatorTest) {
  EXPECT_THROW(Operator("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, constantTest) {
  EXPECT_THROW(Constant("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, expressionTest) {
  EXPECT_THROW(Expression(""), std::invalid_argument);
  EXPECT_THROW(Expression("    "), std::invalid_argument);
}

TEST(InvalidArgumentTests, integerTest) {
  EXPECT_THROW(Integer(""), std::invalid_argument);
  EXPECT_THROW(Integer("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, rationalTest) {
  EXPECT_THROW(Rational(""), std::invalid_argument);
  EXPECT_THROW(Rational("a"), std::invalid_argument);
}
