#include "fintamath/math_objects/MathObjectParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/NodeParser.hpp"
#include "fintamath/math_objects/relations/RelationParser.hpp"

namespace fintamath {
  std::unique_ptr<MathObject> MathObjectParser::parse(const std::string_view &str) {
    if (auto res = RelationParser::parse(str); res) {
      return res;
    }
    return NodeParser::parse(str);
  }
}
