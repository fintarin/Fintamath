#pragma once

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class UnaryPlus : public OperatorCRTP<UnaryPlus, Arithmetic> {
  public:
    UnaryPlus();

    std::string toString() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
