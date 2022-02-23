#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperatorParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/MathObjectParser.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryDivide.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinus.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMultiply.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlus.hpp"

namespace fintamath {
  void BinaryArithmeticOperatorParser::ignoreBrackets(const std::string_view &str, int &position) {
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
    auto firstOperandStr = str.substr(0, splitPosition);
    auto secondOperandStr = str.substr(splitPosition + 1);

    std::shared_ptr<MathObject> firstOperandMathObject = MathObjectParser::parse(firstOperandStr);
    std::shared_ptr<MathObject> secondOperandMathObject = MathObjectParser::parse(secondOperandStr);

    auto firstOperand = std::dynamic_pointer_cast<Node>(firstOperandMathObject);
    auto secondOperand = std::dynamic_pointer_cast<Node>(secondOperandMathObject);
    Set set{firstOperand, secondOperand};

    return std::make_unique<Expression>(set, relation);
  }
  std::unique_ptr<Expression> BinaryArithmeticOperatorParser::parse(const std::string_view &str) {
    auto plusSign = BinaryPlus().toString();
    auto minusSign = BinaryMinus().toString();
    auto multiplySign = BinaryMultiply().toString();
    auto divideSign = BinaryDivide().toString();

    for (int i = str.size() - 1; i >= 0; i--) {
      if (str[i] == plusSign[0] || str[i] == minusSign[0]) {
        if (i == 0) {
          continue;
        }
        if (str[i - 1] == plusSign[0]) {
          continue;
        }
        if (str[i - 1] == minusSign[0]) {
          continue;
        }
        if (str[i - 1] == divideSign[0]) {
          continue;
        }
        if (str[i - 1] == multiplySign[0]) {
          continue;
        }
        if (i == str.size() - 1) {
          throw std::invalid_argument("Expression invalid input");
        }

        std::shared_ptr<Relation> relation;

        if (str[i] == plusSign[0]) {
          relation = std::make_shared<BinaryPlus>();
        }
        if (str[i] == minusSign[0]) {
          relation = std::make_shared<BinaryMinus>();
        }

        return createExpression(str, i, relation);
      }
      if (str[i] == ')') {
        ignoreBrackets(str, i);
      }
    }

    for (int i = str.size() - 1; i >= 0; i--) {
      if (str[i] == multiplySign[0] || str[i] == divideSign[0]) {
        if (i == 0) {
          throw std::invalid_argument("Expression invalid input");
        }
        if (str[i - 1] == plusSign[0]) {
          throw std::invalid_argument("Expression invalid input");
        }
        if (str[i - 1] == minusSign[0]) {
          throw std::invalid_argument("Expression invalid input");
        }
        if (str[i - 1] == divideSign[0]) {
          throw std::invalid_argument("Expression invalid input");
        }
        if (str[i - 1] == multiplySign[0]) {
          throw std::invalid_argument("Expression invalid input");
        }
        if (i == str.size() - 1) {
          throw std::invalid_argument("Expression invalid input");
        }

        std::shared_ptr<Relation> relation;

        if (str[i] == multiplySign[0]) {
          relation = std::make_shared<BinaryMultiply>();
        }
        if (str[i] == divideSign[0]) {
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