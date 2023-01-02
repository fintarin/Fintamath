#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Add : public IOperatorCRTP<Add, IArithmetic, IArithmetic> {
public:
  Add() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  std::string toString() const override {
    return "+";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
