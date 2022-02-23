#pragma once

#include <vector>

#include "fintamath/math_objects/nodes/collections/Collection.hpp"

namespace fintamath {
  class Set : public Collection, public std::vector<std::shared_ptr<Node>> {
  public:
    Set() = default;
    explicit Set(const std::string_view &str);
    Set(const std::initializer_list<std::shared_ptr<Node>> &list);

    std::string toString() const override;
  };
}
