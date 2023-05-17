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

  static MathObjectType getTypeStatic() {
    return MathObjectType::Equiv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
