#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Less : public IOperatorCRTP<Less, IComparable, IComparable> {
public:
  Less() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "<";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
