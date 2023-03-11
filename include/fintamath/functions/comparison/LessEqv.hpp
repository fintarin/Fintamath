#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class LessEqv : public IOperatorCRTP<Boolean, LessEqv, IComparable, IComparable> {
public:
  LessEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "<=";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
