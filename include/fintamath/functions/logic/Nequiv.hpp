#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Nequiv : public IOperatorCRTP<Boolean, Nequiv, Boolean, Boolean> {
public:
  Nequiv() : IOperatorCRTP(IOperator::Priority::Equivalence) {
  }

  std::string toString() const override {
    return "!<->";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
