#include "fintamath/math_objects/nodes/NodeParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/collections/CollectionParser.hpp"
#include "fintamath/math_objects/nodes/expressions/ExpressionParser.hpp"
#include "fintamath/math_objects/nodes/terms/TermParser.hpp"

using namespace fintamath;

std::unique_ptr<Node> NodeParser::parse(const std::string_view &str) {
  auto res = TermParser::parse(str);
  if (res) {
    return res;
  }

  res = CollectionParser::parse(str);
  if (res) {
    return res;
  }

  return ExpressionParser::parse(str);
}
