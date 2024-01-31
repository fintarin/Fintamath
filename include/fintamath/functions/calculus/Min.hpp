#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Min : public IFunctionCRTP<IComparable, Min, IComparable> {
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
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

template <>
struct IsFunctionTypeAny<Min> : std::true_type {};

FINTAMATH_FUNCTION_EXPRESSION(Min, minExpr);

}
