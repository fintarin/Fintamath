#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Boolean;

class Or : public IOperatorCRTP<Or, Boolean, Boolean> {
public:
  Or() : IOperatorCRTP(IOperator::Priority::Or) {
  }

  std::string toString() const override {
    return "||";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
