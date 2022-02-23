#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperatorParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/MathObjectParser.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryDivide.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinus.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMultiply.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlus.hpp"

namespace fintamath {
  static void ignoreBrackets(const std::string_view &str, int &position) {
    position--;
    int leftBracket = 0;
    int rightBracket = 1;

    while (position >= 0) {
      if (str[position] == ')') {
        rightBracket++;
      }
      if (str[position] == '(') {
        leftBracket++;
      }
      if (rightBracket == leftBracket) {
        return;
      }
      position--;
    }
    throw std::invalid_argument("Expression invalid input");
  }
  Set BinaryArithmeticOperatorParser::createSet(const std::string_view &str, int splitPosition) {
    std::shared_ptr<MathObject> firstOperandMathObject = MathObjectParser::parse(str.substr(0, splitPosition));
    std::shared_ptr<MathObject> secondOperandMathObject = MathObjectParser::parse(str.substr(splitPosition + 1));
    auto firstOperand = std::dynamic_pointer_cast<Node>(firstOperandMathObject);
    auto secondOperand = std::dynamic_pointer_cast<Node>(secondOperandMathObject);

    return Set{firstOperand, secondOperand};
  }
  std::unique_ptr<Expression> BinaryArithmeticOperatorParser::parse(const std::string_view &str) {
    auto plusSign = BinaryPlus().toString()[0];
    auto minusSign = BinaryMinus().toString()[0];
    auto multiplySign = BinaryMultiply().toString()[0];
    auto divideSign = BinaryDivide().toString()[0];

    auto expression = std::make_unique<Expression>();

    for (int i = (int)str.size() - 1;; i--) {
      if (str[i] == ')') {
        ignoreBrackets(str, i);
      }

      if (i <= 0) {
        break;
      }

      if (str.at(i - 1) == plusSign || str.at(i - 1) == minusSign || str.at(i - 1) == divideSign ||
          str.at(i - 1) == multiplySign || (str[i] != plusSign && str[i] != minusSign)) {
        continue;
      }

      if (i == str.size() - 1) {
        throw std::invalid_argument("Expression invalid input");
      }

      if (str[i] == plusSign) {
        expression->setRelation(std::make_shared<BinaryPlus>());
      }

      if (str[i] == minusSign) {
        expression->setRelation(std::make_shared<BinaryMinus>());
      }

      if (expression->getRelation() != nullptr) {
        expression->setSet(createSet(str, i));
        return expression;
      }
    }

    for (int i = (int)str.size() - 1;; i--) {
      if (str[i] == ')') {
        ignoreBrackets(str, i);
      }

      if (i <= 0) {
        break;
      }

      if (str[i] != multiplySign && str[i] != divideSign) {
        continue;
      }

      if (i == str.size() - 1 || i == 0 || str.at(i - 1) == plusSign || str.at(i - 1) == minusSign ||
          str.at(i - 1) == divideSign || str.at(i - 1) == multiplySign) {
        throw std::invalid_argument("Expression invalid input");
      }

      if (str[i] == multiplySign) {
        expression->setRelation(std::make_shared<BinaryMultiply>());
      }

      if (str[i] == divideSign) {
        expression->setRelation(std::make_shared<BinaryDivide>());
      }

      if (expression->getRelation() != nullptr) {
        expression->setSet(createSet(str, i));
        return expression;
      }
    }
    return nullptr;
  }
}