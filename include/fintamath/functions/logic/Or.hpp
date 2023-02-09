#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Or : public IOperatorCRTP<Boolean, Or, Boolean, Boolean> {
public:
  Or() : IOperatorCRTP(IOperator::Priority::Or) {
  }

  std::string toString() const override {
    return "|";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
