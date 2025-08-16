#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/expressions/functions/IFunction.hpp"

namespace fintamath {

class Add : public IFunction {
  FINTAMATH_CLASS_BODY(Add, IFunction)

protected:
  Add() = default;

public:
  explicit Add(Children inChildren);

public:
  const FunctionDeclaration &getFunctionDeclaration() const noexcept override;

  std::unique_ptr<IFunction> makeFunctionSelf(Children children) const override;

private:
  static const FunctionDeclaration addDeclaration;
};

}
