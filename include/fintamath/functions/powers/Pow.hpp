#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Pow : public IOperatorCRTP<INumber, Pow, INumber, INumber> {
public:
  Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "^";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
