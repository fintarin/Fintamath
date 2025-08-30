#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Add : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Add, IFunction)

protected:
  Add() = default;
};

class AddOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(AddOper, IFunction)

protected:
  AddOper() = default;

public:
  static Shared<Add> make(Arguments inArgs);
};

}
