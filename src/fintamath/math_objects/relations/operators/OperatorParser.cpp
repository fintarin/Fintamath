#include "fintamath/math_objects/relations/operators/OperatorParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/ArithmeticOperatorParser.hpp"

namespace fintamath {
  std::unique_ptr<Operator> OperatorParser::parse(const std::string_view &str) {
    return ArithmeticOperatorParser::parse(str);
  }
}