#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class PowFunction : public IFunctionCRTP<IArithmetic, PowFunction, IArithmetic, IArithmetic> {
public:
  std::string toString() const override {
    return "pow";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::PowFunction;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

}
