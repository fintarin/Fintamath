#include <gtest/gtest.h>

#include <fstream>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(ExpressionTests, expressionPositiveTests) {
  std::ifstream testsIn(RESOURCES_DIR "positive_tests.txt");
  for (std::string input, output; getline(testsIn, input) && getline(testsIn, output);) {
    std::cout << input << '\n' << output << "\n\n";
    EXPECT_EQ(Expression(input).solve(), output);
    getline(testsIn, input);
  }
}

TEST(ExpressionTests, expressionNegativeTests) {
  std::ifstream testsIn(RESOURCES_DIR "negative_tests.txt");
  for (std::string input, output; getline(testsIn, input);) {
    std::cout << input << '\n' << output << "\n\n";
    EXPECT_ANY_THROW(Expression(input).solve());
  }
}
