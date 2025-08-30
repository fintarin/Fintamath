#pragma once

#include <optional>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {

class Number : public MathObject {
  FINTAMATH_INTERFACE_BODY(Number, MathObject)

public:
  virtual std::optional<unsigned> getPrecision() const noexcept {
    return {};
  }

  virtual bool isComplex() const noexcept {
    return false;
  }
};

}
