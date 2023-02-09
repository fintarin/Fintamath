#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Impl : public IOperatorCRTP<Boolean, Impl, Boolean, Boolean> {
public:
  Impl() : IOperatorCRTP(IOperator::Priority::Implication, false) {
  }

  std::string toString() const override {
    return "->";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
