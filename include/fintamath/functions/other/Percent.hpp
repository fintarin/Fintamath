#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class INumber;

class Percent : public IOperatorCRTP<INumber, Percent, INumber> {
public:
  Percent() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "%";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
