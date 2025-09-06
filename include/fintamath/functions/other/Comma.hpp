#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Comma : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Comma, IFunction)
};

class CommaOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(CommaOper, IFunction)

public:
  static SharedRef<Comma> make(Arguments inArgs);
};

}
