#include <gtest/gtest.h>

#include <fintamath/numbers/Rational.hpp>
#include <fstream>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

//TEST(ExpressionTests, expressionPositiveTests) {
//  std::ifstream testsIn(RESOURCES_DIR "positive_tests.txt");
//  for (std::string input, output; getline(testsIn, input) && getline(testsIn, output);) {
//    std::cout << input << '\n' << output << "\n\n";
//    EXPECT_EQ(Expression(input).solve(), output);
//    getline(testsIn, input);
//  }
//}

TEST(ExpressionTests, parserTest){
  auto a = Expression(" - ( 2 !) ! ^ 3");
}
