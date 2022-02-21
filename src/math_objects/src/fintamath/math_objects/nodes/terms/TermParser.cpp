#include "fintamath/math_objects/nodes/terms/TermParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/numbers/NumberParser.hpp"

using namespace fintamath;

std::unique_ptr<Node> TermParser::parse(const std::string_view &str) {
  return NumberParser::parse(str);
}
