#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionVariadic.hpp"

namespace fintamath {

class Min : public IFunctionVariadic {
  FINTAMATH_FUNCTION_CLASS_BODY(Min, IFunctionVariadic)
};

}
