#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Min : public IFunctionCRTP<IComparable, Min, IComparable> {
  FINTAMATH_FUNCTION_TYPE_ANY()

public:
  Min() : IFunctionCRTP(true) {
  }

  std::string toString() const override {
    return "min";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Min;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
