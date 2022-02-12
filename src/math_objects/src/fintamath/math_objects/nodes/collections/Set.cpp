#include "fintamath/math_objects/nodes/collections/Set.hpp"

using namespace fintamath;

Set::Set(const std::string_view & /*str*/) {
  // TODO
}

Set::Set(const std::initializer_list<NodePtr> &list) : std::vector<NodePtr>(list) {
}

std::string Set::toString() const {
  std::string res = "(";
  for (const auto &node : *this) {
    res += node->toString() + ',';
  }
  res.erase(res.size() - 2);
  return res + ')';
}
