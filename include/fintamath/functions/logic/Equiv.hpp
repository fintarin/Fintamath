#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Boolean;

class Equiv : public IOperatorCRTP<Equiv, Boolean, Boolean> {
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
