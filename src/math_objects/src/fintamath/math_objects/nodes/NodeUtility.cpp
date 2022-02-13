#include "fintamath/math_objects/nodes/NodeUtility.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/collections/CollectionUtility.hpp"
#include "fintamath/math_objects/nodes/expressions/ExpressionUtility.hpp"
#include "fintamath/math_objects/nodes/terms/TermUtility.hpp"

using namespace fintamath;

NodePtr NodeUtility::parse(const std::string_view &str) {
  auto res = TermUtility::parse(str);
  if (res) {
    return res;
  }

  res = CollectionUtility::parse(str);
  if (res) {
    return res;
  }

  return ExpressionUtility::parse(str);
}
