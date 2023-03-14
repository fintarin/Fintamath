#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus : public IOperatorCRTP<IArithmetic, UnaryPlus, IArithmetic> {
public:
  UnaryPlus() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  string toString() const override {
    return "+";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
