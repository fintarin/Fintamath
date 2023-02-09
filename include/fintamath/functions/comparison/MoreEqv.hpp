#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;
class Boolean;

class MoreEqv : public IOperatorCRTP<Boolean, MoreEqv, IComparable, IComparable> {
public:
  MoreEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return ">=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
