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
  std::unique_ptr<Expression>
  BinaryArithmeticOperatorParser::createExpression(const std::string_view &str, int splitPosition,
                                                   const std::shared_ptr<Relation> &relation) {
    std::shared_ptr<MathObject> firstOperandMathObject = MathObjectParser::parse(str.substr(0, splitPosition));
    std::shared_ptr<MathObject> secondOperandMathObject = MathObjectParser::parse(str.substr(splitPosition + 1));
    auto firstOperand = std::dynamic_pointer_cast<Node>(firstOperandMathObject);
    auto secondOperand = std::dynamic_pointer_cast<Node>(secondOperandMathObject);

    return std::make_unique<Expression>((Set){firstOperand, secondOperand}, relation);
  }
  std::unique_ptr<Expression> BinaryArithmeticOperatorParser::parse(const std::string_view &str) {
    auto plusSign = BinaryPlus().toString()[0];
    auto minusSign = BinaryMinus().toString()[0];
    auto multiplySign = BinaryMultiply().toString()[0];
    auto divideSign = BinaryDivide().toString()[0];

    for (int i = (int)str.size() - 1; i > 0; i--) {
      if (str[i] == plusSign || str[i] == minusSign) {
        if (str[i - 1] == plusSign || str[i - 1] == minusSign || str[i - 1] == divideSign ||
            str[i - 1] == multiplySign) {
          continue;
        }
        if (i == str.size() - 1) {
          throw std::invalid_argument("Expression invalid input");
        }
        std::shared_ptr<Relation> relation;
        if (str[i] == plusSign) {
          relation = std::make_shared<BinaryPlus>();
        }
        if (str[i] == minusSign) {
          relation = std::make_shared<BinaryMinus>();
        }

        return createExpression(str, i, relation);
      }
      if (str[i] == ')') {
        ignoreBrackets(str, i);
      }
    }

    for (int i = (int)str.size() - 1; i >= 0; i--) {
      if (str[i] == multiplySign || str[i] == divideSign) {
        if (i == str.size() - 1) {
          throw std::invalid_argument("Expression invalid input");
        }
        if (str[i - 1] == plusSign || str[i - 1] == minusSign || str[i - 1] == divideSign ||
            str[i - 1] == multiplySign) {
          throw std::invalid_argument("Expression invalid input");
        }
        std::shared_ptr<Relation> relation;
        if (str[i] == multiplySign) {
          relation = std::make_shared<BinaryMultiply>();
        }
        if (str[i] == divideSign) {
          relation = std::make_shared<BinaryDivide>();
        }

        return createExpression(str, i, relation);
      }
      if (str[i] == ')') {
        ignoreBrackets(str, i);
      }
    }
    return nullptr;
  }
}