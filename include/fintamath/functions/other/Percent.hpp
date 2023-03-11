#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Percent : public IOperatorCRTP<INumber, Percent, INumber> {
public:
  Percent() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "%";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
