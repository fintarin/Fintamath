#pragma once

#include <optional>

#include "fintamath/core/IComparable.hpp"

namespace fintamath {

class INumber : public IComparable {
  FINTAMATH_CLASS_BODY(INumber, IComparable)

public:
  virtual std::optional<unsigned> getPrecision() const noexcept {
    return {};
  }

  virtual bool isComplex() const noexcept {
    return false;
  }
};

}
