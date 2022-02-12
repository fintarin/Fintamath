#include "fintamath/math_objects/nodes/collections/CollectionUtility.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/collections/Set.hpp"

using namespace fintamath;

NodePtr CollectionUtility::parse(const std::string_view &str) {
  try {
    return std::make_shared<Set>(str);
  } catch (const std::invalid_argument &) {
    // do nothing
  }

  return nullptr;
}
