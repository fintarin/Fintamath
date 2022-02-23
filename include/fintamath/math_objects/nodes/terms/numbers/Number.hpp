#pragma once

#include "fintamath/math_objects/nodes/terms/Term.hpp"

namespace fintamath {
  class Number : public Term {
  public:
    virtual std::unique_ptr<Number> minimize() const = 0;

    ~Number() override = default;
  };
}
