#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperatorParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/MathObjectParser.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryMinus.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryPlus.hpp"

namespace fintamath {
  std::unique_ptr<Expression> UnaryArithmeticOperatorParser::parse(const std::string_view &str) {
    if (str.empty()) {
      throw std::invalid_argument("a");
    }
    auto plusSign = UnaryPlus().toString()[0];
    auto minusSign = UnaryMinus().toString()[0];

    if (str[0] == plusSign || str[0] == minusSign) {
      auto operandStr = str.substr(1, str.size() - 1);
      std::shared_ptr<MathObject> operandMathObject = MathObjectParser::parse(operandStr);
      auto operand = std::dynamic_pointer_cast<Node>(operandMathObject);

      Set set{operand};

      std::shared_ptr<Relation> relation;

      if (str[0] == minusSign) {
        relation = std::make_shared<UnaryMinus>();
      }
      if (str[0] == plusSign) {
        relation = std::make_shared<UnaryPlus>();
      }
      return std::make_unique<Expression>(set, relation);
    }
    return nullptr;
  }
}