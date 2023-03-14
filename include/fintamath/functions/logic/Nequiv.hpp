#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Nequiv : public IOperatorCRTP<Boolean, Nequiv, Boolean, Boolean> {
public:
  Nequiv() : IOperatorCRTP(IOperator::Priority::Equivalence) {
  }

  string toString() const override {
    return "!<->";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
