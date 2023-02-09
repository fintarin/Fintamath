#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Equiv : public IOperatorCRTP<Boolean, Equiv, Boolean, Boolean> {
public:
  Equiv() : IOperatorCRTP(IOperator::Priority::Equivalence) {
  }

  std::string toString() const override {
    return "<->";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
