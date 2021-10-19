#include <calculator/Calculator.hpp>
#include <fstream>
#include <gtest/gtest.h>

TEST(CalculatorTests, positiveTets) {
  std::ifstream testsIn(RESOURCES_DIR "positive_tests.txt");
  Calculator calc;
  for (std::string input, output; std::getline(testsIn, input) && std::getline(testsIn, output);) {
    std::cout << input << '\n' << output << "\n\n";
    EXPECT_EQ(calc.calculate(input), output);
    std::getline(testsIn, input);
  }
}

TEST(CalculatorTests, negativeTets) {
  std::ifstream testsIn(RESOURCES_DIR "negative_tests.txt");
  Calculator calc;
  for (std::string input, output; std::getline(testsIn, input);) {
    std::cout << input << '\n' << output << "\n\n";
    EXPECT_ANY_THROW(calc.calculate(input));
    std::getline(testsIn, input);
  }
}
