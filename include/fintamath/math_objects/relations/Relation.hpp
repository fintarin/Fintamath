#pragma once

#include "fintamath/math_objects/nodes/collections/Set.hpp"

namespace fintamath {
  class Relation : public MathObject {
  public:
    virtual std::unique_ptr<Node> operator()(const Set &set) const = 0;
    ~Relation() override = default;
  };
}
