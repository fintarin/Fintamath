#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Div : public IOperatorCRTP<IArithmetic, Div, IArithmetic, IArithmetic> {
public:
  Div() : IOperatorCRTP(IOperator::Priority::Multiplication, false) {
  }

  string toString() const override {
    return "/";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
