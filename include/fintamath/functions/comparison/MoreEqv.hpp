#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class MoreEqv : public IOperatorCRTP<Boolean, MoreEqv, IComparable, IComparable> {
public:
  MoreEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  string toString() const override {
    return ">=";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
