#pragma once

#include "fintamath/math_objects/MathObject.hpp"
#include "fintamath/math_objects/nodes/collections/Set.hpp"

namespace fintamath {
  class Relation : public MathObject {
  public:
    virtual Set operator()(const Set &set, int64_t precision = 0) const = 0;
    ~Relation() override = default;
  };
}
