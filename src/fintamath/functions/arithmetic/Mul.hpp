#pragma once

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class Mul : public OperatorCRTP<Mul, Arithmetic, Arithmetic> {
  public:
    Mul();

    std::string toString() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
