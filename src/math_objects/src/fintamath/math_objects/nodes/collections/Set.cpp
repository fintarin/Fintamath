#include "fintamath/math_objects/nodes/collections/Set.hpp"

#include <stdexcept>

using namespace fintamath;

Set::Set(const std::string_view & /*str*/) {
  throw std::invalid_argument("Set invalid input");
}

Set::Set(const std::initializer_list<std::shared_ptr<Node>> &list) : std::vector<std::shared_ptr<Node>>(list) {
}

std::string Set::toString() const {
  std::string res = "{";
  for (const auto &node : *this) {
    res += node->toString() + ",";
  }
  res.erase(res.size() - 1);
  return res + "}";
}
