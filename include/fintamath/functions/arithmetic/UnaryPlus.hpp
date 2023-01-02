#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus : public IOperatorCRTP<UnaryPlus, IArithmetic> {
public:
  UnaryPlus() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "+";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
