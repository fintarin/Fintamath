#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionVariadic.hpp"

namespace fintamath {

class Comma : public IFunctionVariadic {
  FINTAMATH_FUNCTION_CLASS_BODY(Comma, IFunctionVariadic)

public:
  ArgVector toFunctionArgs() const;
};

}
