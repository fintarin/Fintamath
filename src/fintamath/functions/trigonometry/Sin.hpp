#pragma once

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Sin : public FunctionCRTP<Sin, Arithmetic> {
  public:
    Sin() = default;

    std::string toString() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
