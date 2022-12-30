#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Percent : public IOperatorCRTP<Percent, INumber> {
public:
  Percent() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "%";
  }

protected:
  Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
};

}
