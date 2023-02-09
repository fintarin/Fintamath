#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;
class Boolean;

class Less : public IOperatorCRTP<Boolean, Less, IComparable, IComparable> {
public:
  Less() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "<";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
