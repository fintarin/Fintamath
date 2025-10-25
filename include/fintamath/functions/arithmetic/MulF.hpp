#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionVariadic.hpp"

namespace fintamath {

class MulF : public IFunctionVariadic {
  FINTAMATH_FUNCTION_CLASS_BODY(MulF, IFunctionVariadic)

protected:
  SharedPtr<IMathObject> preSimplifySelf() const override;
};

}
