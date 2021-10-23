#include <calculator/Calculator.hpp>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;

TEST(CalculatorTests, calculationPositiveTests) {
  ifstream testsIn(RESOURCES_DIR "positive_tests.txt");
  Calculator calc;
  for (string input, output; getline(testsIn, input) && getline(testsIn, output);) {
    cout << input << '\n' << output << "\n\n";
    EXPECT_EQ(calc.calculate(input), output);
    getline(testsIn, input);
  }
}

TEST(CalculatorTests, calculationNegativeTests) {
  ifstream testsIn(RESOURCES_DIR "negative_tests.txt");
  Calculator calc;
  for (string input, output; getline(testsIn, input);) {
    cout << input << '\n' << output << "\n\n";
    EXPECT_ANY_THROW(calc.calculate(input));
    getline(testsIn, input);
  }
}

TEST(CalculatorTests, getSetPrecisionTest) {
  const int precision = 100;
  Calculator calc;
  calc.setPrecision(100);
  EXPECT_EQ(calc.getPrecision(), precision);
}
