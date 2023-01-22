#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Boolean;

class Impl : public IOperatorCRTP<Impl, Boolean, Boolean> {
public:
  Impl() : IOperatorCRTP(IOperator::Priority::Implication) {
  }

  std::string toString() const override {
    return "->";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
