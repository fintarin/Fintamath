#pragma once

#include "fintamath/functions/FintamathFunctionClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Add : public IFunction {
  FINTAMATH_FUNCTION_CLASS_BODY(Add, IFunction)

protected:
  Add() = default;

  explicit Add(Arguments inArgs);

public:
  const FunctionDeclaration &getFunctionDeclaration() const noexcept override;

  static std::unique_ptr<Add> make(Arguments inArgs);

private:
  static const FunctionDeclaration addDeclaration;
};

}
