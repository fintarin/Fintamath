#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunctionBinary.hpp"

namespace fintamath {

class Pow : public IFunctionBinary {
  FINTAMATH_FUNCTION_CLASS_BODY(Pow, IFunctionBinary)

public:
  std::string toString() const noexcept override;
};

}
