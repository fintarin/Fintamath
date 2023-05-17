#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acot : public IFunctionCRTP<INumber, Acot, INumber> {
public:
  Acot() = default;

  std::string toString() const override {
    return "acot";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Acot;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
