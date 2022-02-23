#pragma once

#include "fintamath/math_objects/nodes/terms/Term.hpp"

namespace fintamath {
  class Constant : public Term {
  public:
    ~Constant() override = default;
  };
}
