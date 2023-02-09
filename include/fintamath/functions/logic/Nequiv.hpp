#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Boolean;

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
