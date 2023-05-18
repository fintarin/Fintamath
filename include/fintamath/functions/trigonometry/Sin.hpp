#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sin : public IFunctionCRTP<INumber, Sin, INumber> {
public:
  Sin() = default;

  std::string toString() const override {
    return "sin";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Sin);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
