#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Boolean;

class Not : public IOperatorCRTP<Not, Boolean> {
public:
  Not() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "!";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
