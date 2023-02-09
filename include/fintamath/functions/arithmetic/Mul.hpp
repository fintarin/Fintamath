#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IArithmetic;

class Mul : public IOperatorCRTP<IArithmetic, Mul, IArithmetic, IArithmetic> {
public:
  Mul() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string toString() const override {
    return "*";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
