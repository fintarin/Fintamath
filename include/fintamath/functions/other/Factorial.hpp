#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class INumber;

class Factorial : public IOperatorCRTP<Factorial, INumber> {
public:
  Factorial() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "!";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
