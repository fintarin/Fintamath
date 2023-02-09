#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IArithmetic;

class Add : public IOperatorCRTP<IArithmetic, Add, IArithmetic, IArithmetic> {
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
