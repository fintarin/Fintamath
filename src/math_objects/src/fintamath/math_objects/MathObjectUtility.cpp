#include "fintamath/math_objects/MathObjectUtility.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/NodeUtility.hpp"
#include "fintamath/math_objects/relations/RelationUtility.hpp"

using namespace fintamath;

MathObjectPtr MathObjectUtility::parse(const std::string_view &str) {
  auto res = NodeUtility::parse(str);
  if (res) {
    return res;
  }

  return RelationUtility::parse(str);
}
