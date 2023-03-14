#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Not : public IOperatorCRTP<Boolean, Not, Boolean> {
public:
  Not() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  string toString() const override {
    return "~";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
