#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Sub : public IOperatorCRTP<IArithmetic, Sub, IArithmetic, IArithmetic> {
public:
  Sub() : IOperatorCRTP(IOperator::Priority::Addition, false) {
  }

  string toString() const override {
    return "-";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
