#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Sub : public IOperatorCRTP<IArithmetic, Sub, IArithmetic, IArithmetic> {
public:
  Sub() : IOperatorCRTP(IOperator::Priority::Addition, false) {
  }

  std::string toString() const override {
    return "-";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
