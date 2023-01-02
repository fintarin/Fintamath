#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class LessEqv : public IOperatorCRTP<LessEqv, IComparable, IComparable> {
public:
  LessEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "<=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
