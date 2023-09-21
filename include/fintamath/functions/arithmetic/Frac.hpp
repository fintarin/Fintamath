#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Frac : public IFunctionCRTP<IArithmetic, Frac, IArithmetic, IArithmetic> {
public:
  std::string toString() const override {
    return "frac";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Frac;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
