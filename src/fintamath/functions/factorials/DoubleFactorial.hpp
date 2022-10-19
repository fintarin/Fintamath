#pragma once

#include "fintamath/functions/Operator.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  class DoubleFactorial : public OperatorCRTP<DoubleFactorial, Integer> {
  public:
    DoubleFactorial();

    std::string toString() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
