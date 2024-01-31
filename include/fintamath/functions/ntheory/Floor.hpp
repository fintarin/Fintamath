#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Floor : public IFunctionCRTP<INumber, Floor, INumber> {
public:
  Floor() = default;

  std::string toString() const override {
    return "floor";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Floor;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiFloorSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Floor, floorExpr);

}
