#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IComparable;

class More : public IOperatorCRTP<More, IComparable, IComparable> {
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
