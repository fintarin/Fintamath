#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class Eqv : public IOperatorCRTP<Eqv, IComparable, IComparable> {
  public:
    Eqv();

    std::string toString() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
