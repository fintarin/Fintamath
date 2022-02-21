#pragma once

#include "fintamath/math_objects/nodes/terms/Term.hpp"

class Constant : public Term {
public:
  ~Constant() override = default;
};
