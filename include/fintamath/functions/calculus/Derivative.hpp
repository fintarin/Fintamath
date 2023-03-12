#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Derivative : public IOperatorCRTP<IComparable, Derivative, IComparable> {
public:
  Derivative() : IOperatorCRTP(IOperator::Priority::PostfixUnary, true, false) {
  }

  std::string toString() const override {
    return "'";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
