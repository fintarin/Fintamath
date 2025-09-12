#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionVariadic.hpp"

namespace fintamath {

class Mul : public IFunctionVariadic {
  FINTAMATH_FUNCTION_CLASS_BODY(Mul, IFunctionVariadic)
};

}
