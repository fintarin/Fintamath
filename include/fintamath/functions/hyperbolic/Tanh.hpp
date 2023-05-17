#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Tanh : public IFunctionCRTP<INumber, Tanh, INumber> {
public:
  Tanh() = default;

  std::string toString() const override {
    return "tanh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Tanh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
