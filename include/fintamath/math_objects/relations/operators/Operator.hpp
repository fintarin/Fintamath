#pragma once

#include "fintamath/math_objects/relations/Relation.hpp"

namespace fintamath {
  class Operator : public Relation {
  public:
    ~Operator() override = default;

    virtual int getPriority() const = 0;
    virtual bool isAssociative() const = 0;
  };
}
