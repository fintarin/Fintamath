#include "fintamath/math_objects/nodes/NodeParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/ParserInjector.hpp"
#include "fintamath/math_objects/nodes/collections/CollectionParser.hpp"
#include "fintamath/math_objects/nodes/expressions/ExpressionParser.hpp"
#include "fintamath/math_objects/nodes/terms/TermParser.hpp"

namespace fintamath {
  std::unique_ptr<Node> NodeParser::parse(const std::string_view &str) {
    INJECT_PARSER(TermParser, str)
    INJECT_PARSER(CollectionParser, str)
    INJECT_PARSER(ExpressionParser, str)
    return nullptr;
  }
}
