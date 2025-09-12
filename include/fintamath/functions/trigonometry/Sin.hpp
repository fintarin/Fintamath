#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionUnary.hpp"

namespace fintamath {

class Sin : public IFunctionUnary {
  FINTAMATH_FUNCTION_CLASS_BODY(Sin, IFunctionUnary)

protected:
  SharedPtr<IMathObject> approximateSelf() const override;
};

}
