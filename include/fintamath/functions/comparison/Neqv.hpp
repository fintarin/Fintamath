#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;
class Boolean;

class Neqv : public IOperatorCRTP<Boolean, Neqv, IComparable, IComparable> {
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
