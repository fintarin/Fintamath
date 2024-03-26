#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class PowFunction final : public IFunctionCRTP<IArithmetic, PowFunction, IArithmetic, IArithmetic> {
  FINTAMATH_CLASS_BODY(PowFunction)

public:
  std::string toString() const override {
    return "pow";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
