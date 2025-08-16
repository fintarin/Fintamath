#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Comma : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(Comma, IFunction)

protected:
  Comma() = default;

public:
  static std::unique_ptr<Comma> make(Arguments inArgs);
};

class CommaOper : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(CommaOper, IFunction)

protected:
  CommaOper() = default;

public:
  static std::unique_ptr<Comma> make(Arguments inArgs);
};

}
