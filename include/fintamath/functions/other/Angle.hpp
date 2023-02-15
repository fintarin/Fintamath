#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Angle : public IOperatorCRTP<INumber, Angle, INumber> {
public:
  Angle() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "°";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
