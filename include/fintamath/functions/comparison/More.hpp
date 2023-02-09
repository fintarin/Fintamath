#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;
class Boolean;

class More : public IOperatorCRTP<Boolean, More, IComparable, IComparable> {
public:
  More() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return ">";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
