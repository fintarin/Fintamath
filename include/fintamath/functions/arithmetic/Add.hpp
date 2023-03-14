#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Add : public IOperatorCRTP<IArithmetic, Add, IArithmetic, IArithmetic> {
public:
  Add() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  string toString() const override {
    return "+";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
