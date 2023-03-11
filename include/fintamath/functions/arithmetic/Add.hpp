#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Add : public IOperatorCRTP<IArithmetic, Add, IArithmetic, IArithmetic> {
public:
  Add() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  std::string toString() const override {
    return "+";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
