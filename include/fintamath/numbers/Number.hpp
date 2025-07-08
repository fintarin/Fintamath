#pragma once

#include <optional>

#include "fintamath/core/Comparable.hpp"

namespace fintamath {

class Number : public Comparable {
  FINTAMATH_CLASS_BODY(Number, Comparable)

public:
  virtual std::optional<unsigned> getPrecision() const noexcept {
    return {};
  }

  virtual bool isComplex() const noexcept {
    return false;
  }
};

}
