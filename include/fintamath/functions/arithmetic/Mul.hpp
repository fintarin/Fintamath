#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Mul : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Mul, IFunction)

protected:
  Mul() = default;
};

class MulOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(MulOper, IFunction)

protected:
  MulOper() = default;

public:
  static Shared<Mul> make(Arguments inArgs);
};

}
