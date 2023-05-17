#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Or : public IOperatorCRTP<Boolean, Or, Boolean, Boolean> {
public:
  Or() : IOperatorCRTP(IOperator::Priority::Or) {
  }

  std::string toString() const override {
    return "|";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Or;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
