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

  static MathObjectType getTypeStatic() {
    return MathObjectType::Nequiv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
