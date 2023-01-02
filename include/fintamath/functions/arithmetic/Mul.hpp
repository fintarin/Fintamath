#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Mul : public IOperatorCRTP<Mul, IArithmetic, IArithmetic> {
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
