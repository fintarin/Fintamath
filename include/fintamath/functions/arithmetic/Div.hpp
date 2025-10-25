#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionBinary.hpp"

namespace fintamath {

class Div : public IFunctionBinary {
  FINTAMATH_FUNCTION_CLASS_BODY(Div, IFunctionBinary)

public:
  std::string toString() const noexcept override;
};

}
