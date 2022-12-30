#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  class Pow : public IOperatorCRTP<Pow, INumber, INumber> {
  public:
    Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation) {
    }

    std::string toString() const {
      return "^";
    }

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
