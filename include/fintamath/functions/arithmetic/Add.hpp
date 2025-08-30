#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Add : public IFunction {
  FINTAMATH_CLASS_BODY(Add, IFunction)

protected:
  Add() = default;

  explicit Add(Arguments inArgs);

public:
  const FunctionDeclaration &getFunctionDeclaration() const noexcept override;

  std::unique_ptr<IFunction> makeFunctionSelf(Arguments inArgs) const override;

private:
  static const FunctionDeclaration addDeclaration;
};

}
