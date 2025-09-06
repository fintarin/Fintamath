#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Mul : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Mul, IFunction)
};

class MulOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(MulOper, IFunction)

public:
  static SharedRef<Mul> make(Arguments inArgs);
};

}
