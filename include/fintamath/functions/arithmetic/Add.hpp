#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Add : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(Add, IFunction)

protected:
  Add() = default;

public:
  static std::unique_ptr<Add> make(Arguments inArgs);
};

class AddOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(AddOper, IFunction)

protected:
  AddOper() = default;

public:
  static std::unique_ptr<Add> make(Arguments inArgs);
};

}
