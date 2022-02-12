#include "fintamath/math_objects/nodes/terms/numbers/NumberUtility.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

using namespace fintamath;

NodePtr NumberUtility::parse(const std::string_view &str) {
  try {
    return std::make_shared<Integer>(str);
  } catch (const std::invalid_argument &) {
    // do nothing
  }

  try {
    return std::make_shared<Rational>(str);
  } catch (const std::invalid_argument &) {
    // do nothing
  }

  return nullptr;
}
