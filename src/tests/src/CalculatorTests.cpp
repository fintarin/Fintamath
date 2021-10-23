#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "calculator/Calculator.hpp"

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
  }
}

TEST(CalculatorTests, getETest) {
  const int precision = 100;
  Calculator calc;
  calc.setPrecision(100);
  EXPECT_EQ(calc.calculate("e"),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274");
}

TEST(CalculatorTests, getSetPrecisionTest) {
  const int precision = 100;
  Calculator calc;
  calc.setPrecision(100);
  EXPECT_EQ(calc.getPrecision(), precision);
  calc.setPrecision(-1);
  EXPECT_EQ(calc.getPrecision(), 1);
}
