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
      std::unique_ptr<Expression> expression;

      std::shared_ptr<MathObject> operandMathObject = MathObjectParser::parse(str.substr(1, str.size() - 1));

      expression->setSet(Set{std::dynamic_pointer_cast<Node>(operandMathObject)});

      if (str[0] == minusSign) {
        expression->setRelation(std::make_shared<UnaryMinus>());
      }
      if (str[0] == plusSign) {
        expression->setRelation(std::make_shared<UnaryPlus>());
      }
      return expression;
    }
    return nullptr;
  }
}