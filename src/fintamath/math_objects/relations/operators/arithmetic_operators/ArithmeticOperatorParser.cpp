#include "fintamath/math_objects/relations/operators/arithmetic_operators/ArithmeticOperatorParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperatorParser.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperatorParser.hpp"

namespace fintamath {
  std::unique_ptr<Expression> ArithmeticOperatorParser::parse(const std::string_view &str) {
    if (auto res = BinaryArithmeticOperatorParser::parse(str); res) {
      return res;
    }
    return UnaryArithmeticOperatorParser::parse(str);
  }
}
