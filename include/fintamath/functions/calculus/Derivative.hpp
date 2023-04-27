#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Derivative : public IOperatorCRTP<IComparable, Derivative, IComparable> {
public:
  Derivative() : IOperatorCRTP(IOperator::Priority::PostfixUnary, true) {
  }

  string toString() const override {
    return "'";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
