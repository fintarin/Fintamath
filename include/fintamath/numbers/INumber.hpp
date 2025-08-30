#pragma once

#include <optional>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class INumber : public IMathObject {
  FINTAMATH_INTERFACE_BODY(INumber, IMathObject)

public:
  virtual std::optional<unsigned> getPrecision() const noexcept {
    return {};
  }

  virtual bool isComplex() const noexcept {
    return false;
  }
};

}
