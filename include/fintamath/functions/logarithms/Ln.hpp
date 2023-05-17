#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Ln : public IFunctionCRTP<INumber, Ln, INumber> {
public:
  Ln() = default;

  std::string toString() const override {
    return "ln";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Ln;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
