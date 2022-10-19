#pragma once

#include "fintamath/core/MathObject.hpp"
#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class Eq : public OperatorCRTP<Eq, MathObject, MathObject> {
  public:
    Eq();

    std::string toString() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
