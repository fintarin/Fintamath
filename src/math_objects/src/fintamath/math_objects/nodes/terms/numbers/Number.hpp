#pragma once

#include "fintamath/math_objects/nodes/terms/Term.hpp"

namespace fintamath {
  class Number : public Term {
  public:
    ~Number() override = default;
  };
}
