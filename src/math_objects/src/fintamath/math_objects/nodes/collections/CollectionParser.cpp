#include "fintamath/math_objects/nodes/collections/CollectionParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/collections/Set.hpp"

namespace fintamath {
  std::unique_ptr<Node> CollectionParser::parse(const std::string_view &str) {
    try {
      return std::make_unique<Set>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }
    return nullptr;
  }
}
