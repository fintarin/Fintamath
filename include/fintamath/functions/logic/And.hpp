#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class And : public IOperatorCRTP<Boolean, And, Boolean, Boolean> {
public:
  And() : IOperatorCRTP(IOperator::Priority::And) {
  }

  string toString() const override {
    return "&";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
