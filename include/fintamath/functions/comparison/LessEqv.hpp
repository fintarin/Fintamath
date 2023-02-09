#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;
class Boolean;

class LessEqv : public IOperatorCRTP<Boolean, LessEqv, IComparable, IComparable> {
public:
  LessEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "<=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
