#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Equiv : public IOperatorCRTP<Boolean, Equiv, Boolean, Boolean> {
public:
  Equiv() : IOperatorCRTP(IOperator::Priority::Equivalence) {
  }

  string toString() const override {
    return "<->";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
