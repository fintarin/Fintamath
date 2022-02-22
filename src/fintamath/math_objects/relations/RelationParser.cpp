#include "fintamath/math_objects/relations/RelationParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/TermParser.hpp"
#include "fintamath/math_objects/relations/operators/OperatorParser.hpp"

namespace fintamath {
  std::unique_ptr<Expression> RelationParser::parse(const std::string_view &str) {
    return OperatorParser::parse(str);
  }
}