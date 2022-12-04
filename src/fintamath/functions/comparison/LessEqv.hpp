#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class LessEqv : public IOperatorCRTP<LessEqv, IComparable, IComparable> {
  public:
    LessEqv();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
