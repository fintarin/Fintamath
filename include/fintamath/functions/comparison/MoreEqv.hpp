#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class MoreEqv : public IOperatorCRTP<MoreEqv, IComparable, IComparable> {
  public:
    MoreEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
    }

    std::string toString() const {
      return ">=";
    }

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
