#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class FracMixed final : public IFunctionCRTP<IArithmetic, FracMixed, IArithmetic, IArithmetic, IArithmetic> {
public:
  std::string toString() const override {
    return "frac";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::FracMixed;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
