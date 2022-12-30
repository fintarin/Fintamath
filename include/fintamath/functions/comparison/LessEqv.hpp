#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class LessEqv : public IOperatorCRTP<LessEqv, IComparable, IComparable> {
  public:
    LessEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
    }

    std::string toString() const {
      return "<=";
    }

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
