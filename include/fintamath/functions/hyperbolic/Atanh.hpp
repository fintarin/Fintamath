#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atanh : public IFunctionCRTP<INumber, Atanh, INumber> {
public:
  Atanh() = default;

  std::string toString() const override {
    return "atanh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Atanh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
