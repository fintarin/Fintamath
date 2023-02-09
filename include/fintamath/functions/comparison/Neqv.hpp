#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Neqv : public IOperatorCRTP<Boolean, Neqv, IComparable, IComparable> {
public:
  Neqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "!=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
