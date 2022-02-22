#pragma once

#include "fintamath/math_objects/nodes/collections/Collection.hpp"

namespace fintamath {
  class CollectionParser final {
  public:
    CollectionParser() = delete;

    static std::unique_ptr<Collection> parse(const std::string_view &str);
  };
}
