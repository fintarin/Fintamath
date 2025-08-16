#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Sin : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Sin, IFunction)

protected:
  Sin() = default;
};

}
