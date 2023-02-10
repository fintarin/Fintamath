#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Derivative : public IOperatorCRTP<IComparable, Derivative, IComparable> {
public:
  Derivative() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "'";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
