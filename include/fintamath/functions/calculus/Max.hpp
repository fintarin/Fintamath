#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Max final : public IFunctionCRTP<IComparable, Max, IComparable> {
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
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

template <>
struct IsFunctionTypeAny<Max> : std::true_type {};

FINTAMATH_FUNCTION_EXPRESSION(Max, maxExpr);

}
