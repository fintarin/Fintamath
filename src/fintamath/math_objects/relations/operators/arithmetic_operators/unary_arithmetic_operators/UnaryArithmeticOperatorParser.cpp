#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperatorParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/MathObjectParser.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryMinus.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryPlus.hpp"

namespace fintamath {
  std::unique_ptr<Expression> UnaryArithmeticOperatorParser::parse(const std::string_view &str) {
    if (str.size() == 0) {
      throw std::invalid_argument("a");
    }
    if (str[0] == UnaryMinus().toString().at(0) || str[0] == UnaryPlus().toString().at(0)) {
      auto operandStr = str.substr(1, str.size() - 1);
      std::shared_ptr<MathObject> operandMathObject = MathObjectParser::parse(operandStr);
      auto operand = std::dynamic_pointer_cast<Node>(operandMathObject);

      Set set{operand};

      std::shared_ptr<Relation> relation;

      if (str[0] == UnaryMinus().toString().at(0)) {
        relation = std::make_shared<UnaryMinus>();
      }
      if (str[0] == UnaryPlus().toString().at(0)) {
        relation = std::make_shared<UnaryPlus>();
      }
      return std::make_unique<Expression>(set, relation);
    }
    return nullptr;
  }
}