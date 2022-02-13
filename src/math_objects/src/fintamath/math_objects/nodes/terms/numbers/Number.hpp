#pragma once

#include "fintamath/math_objects/nodes/terms/Term.hpp"

namespace fintamath {
  class Number : public Term {
  public:
    virtual NodePtr minimize() const = 0;

    ~Number() override = default;
  };
}
