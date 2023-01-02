#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Pow : public IOperatorCRTP<Pow, INumber, INumber> {
public:
  Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation) {
  }

  std::string toString() const override {
    return "^";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
