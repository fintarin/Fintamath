#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Mul : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(Mul, IFunction)

protected:
  Mul() = default;

public:
  static std::unique_ptr<Mul> make(Arguments inArgs);
};

class MulOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(MulOper, IFunction)

protected:
  MulOper() = default;

public:
  static std::unique_ptr<Mul> make(Arguments inArgs);
};

}
