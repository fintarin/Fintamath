#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Max : public IFunctionCRTP<IComparable, Max, IComparable> {
  FINTAMATH_FUNCTION_TYPE_ANY()

public:
  Max() : IFunctionCRTP(true) {
  }

  std::string toString() const override {
    return "max";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Max;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
