#include <gtest/gtest.h>

#include <stdexcept>

#include "expressions/Expression.hpp"
#include "single_entities/operators/Function.hpp"
#include "single_entities/operators/Operator.hpp"
#include "single_entities/terms/literals/Constant.hpp"
#include "single_entities/terms/numbers/Integer.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

using namespace std;

TEST(InvalidArgumentTests, functionTest) {
  EXPECT_THROW(Function("a"), invalid_argument);
}

TEST(InvalidArgumentTests, operatorTest) {
  EXPECT_THROW(Operator("a"), invalid_argument);
}

TEST(InvalidArgumentTests, constantTest) {
  EXPECT_THROW(Constant("a"), invalid_argument);
}

TEST(InvalidArgumentTests, expressionTest) {
  EXPECT_THROW(Expression(""), invalid_argument);
  EXPECT_THROW(Expression("    "), invalid_argument);
}

TEST(InvalidArgumentTests, integerTest) {
  EXPECT_THROW(Integer(""), invalid_argument);
  EXPECT_THROW(Integer("a"), invalid_argument);
}

TEST(InvalidArgumentTests, rationalTest) {
  EXPECT_THROW(Rational(""), invalid_argument);
  EXPECT_THROW(Rational("a"), invalid_argument);
}
