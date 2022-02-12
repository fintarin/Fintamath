#include "fintamath/math_objects/nodes/terms/TermUtility.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/numbers/NumberUtility.hpp"

using namespace fintamath;

NodePtr TermUtility::parse(const std::string_view &str) {
  return NumberUtility::parse(str);
}
