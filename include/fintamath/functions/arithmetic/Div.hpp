#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IArithmetic;

class Div : public IOperatorCRTP<Div, IArithmetic, IArithmetic> {
public:
  Div() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string toString() const override {
    return "/";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
