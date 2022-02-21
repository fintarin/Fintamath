#include "fintamath/math_objects/nodes/collections/CollectionParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/collections/Set.hpp"

using namespace fintamath;

NodePtr CollectionParser::parse(const std::string_view &str) {
  try {
    return std::make_shared<Set>(str);
  } catch (const std::invalid_argument &) {
    // do nothing
  }
  return nullptr;
}
