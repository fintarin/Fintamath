#include <gtest/gtest.h>

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"
#include "fintamath/math_objects/relations/functions/Function.hpp"
#include "fintamath/math_objects/relations/operators/Operator.hpp"
#include "fintamath/math_objects/nodes/terms/constants/Constant.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Integer.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

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
