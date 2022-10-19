#pragma once

#include "fintamath/functions/Operator.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  class Factorial : public OperatorCRTP<Factorial, Integer> {
  public:
    Factorial();

    std::string toString() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
