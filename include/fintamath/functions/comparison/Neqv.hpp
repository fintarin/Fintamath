#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;

class Neqv : public IOperatorCRTP<Neqv, IComparable, IComparable> {
public:
  Neqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "!=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
