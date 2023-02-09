#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;
class Boolean;

class Eqv : public IOperatorCRTP<Boolean, Eqv, IComparable, IComparable> {
public:
  Eqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
