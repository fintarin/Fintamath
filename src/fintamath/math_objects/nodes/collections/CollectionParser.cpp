#include "fintamath/math_objects/nodes/collections/CollectionParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/ParserInjector.hpp"
#include "fintamath/math_objects/nodes/collections/Set.hpp"

namespace fintamath {
  std::unique_ptr<Collection> CollectionParser::parse(const std::string_view &str) {
    INJECT_CONSTRUCTOR(Set, str)
    return nullptr;
  }
}
