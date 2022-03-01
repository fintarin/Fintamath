#include "fintamath/math_objects/nodes/terms/numbers/NumberParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/ParserInjector.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

namespace fintamath {
  std::unique_ptr<Number> NumberParser::parse(const std::string_view &str) {
    INJECT_CONSTRUCTOR(Integer, str)
    INJECT_CONSTRUCTOR(Rational, str)
    return nullptr;
  }
}
