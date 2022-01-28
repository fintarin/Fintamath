#include <gtest/gtest.h>

#include <stdexcept>

#include "fintamath/math_objects/nodes/expressions/ArithmeticExpression.hpp"
#include "fintamath/math_objects/relations/functions/ElementaryFunction.hpp"
#include "fintamath/math_objects/relations/operators/ArithmeticOperator.hpp"
#include "fintamath/math_objects/nodes/terms/constants/MathConstant.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Integer.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

TEST(InvalidArgumentTests, functionTest) {
  EXPECT_THROW(ElementaryFunction("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, operatorTest) {
  EXPECT_THROW(ArithmeticOperator("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, constantTest) {
  EXPECT_THROW(MathConstant("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, expressionTest) {
  EXPECT_THROW(ArithmeticExpression(""), std::invalid_argument);
  EXPECT_THROW(ArithmeticExpression("    "), std::invalid_argument);
}

TEST(InvalidArgumentTests, integerTest) {
  EXPECT_THROW(Integer(""), std::invalid_argument);
  EXPECT_THROW(Integer("a"), std::invalid_argument);
}

TEST(InvalidArgumentTests, rationalTest) {
  EXPECT_THROW(Rational(""), std::invalid_argument);
  EXPECT_THROW(Rational("a"), std::invalid_argument);
}
