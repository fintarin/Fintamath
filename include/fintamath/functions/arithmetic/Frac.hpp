#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Frac final : public IFunctionCRTP<IArithmetic, Frac, IArithmetic, IArithmetic> {
  FINTAMATH_CLASS_BODY(Frac)

public:
  std::string toString() const override {
    return "frac";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
