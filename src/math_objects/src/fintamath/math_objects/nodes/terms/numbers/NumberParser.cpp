#include "fintamath/math_objects/nodes/terms/numbers/NumberParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

namespace fintamath {
  std::unique_ptr<Node> NumberParser::parse(const std::string_view &str) {
    try {
      return std::make_unique<Integer>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }
    try {
      return std::make_unique<Rational>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }
    return nullptr;
  }
}
