#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class And : public IOperatorCRTP<And, Boolean, Boolean> {
public:
  And() : IOperatorCRTP(IOperator::Priority::And) {
  }

  std::string toString() const override {
    return "&&";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
