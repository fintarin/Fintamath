#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IArithmetic;

class Neg : public IOperatorCRTP<Neg, IArithmetic> {
public:
  Neg() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "-";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
