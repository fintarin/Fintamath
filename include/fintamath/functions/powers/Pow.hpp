#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class INumber;

class Pow : public IOperatorCRTP<INumber, Pow, INumber, INumber> {
public:
  Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "^";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
