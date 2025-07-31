#pragma once

#include "fintamath/expressions/ExpressionBase.hpp"
#include "fintamath/expressions/functions/Function.hpp"

namespace fintamath {

class Add : public Function {
  FINTAMATH_CLASS_BODY(Add, Function)

protected:
  Add() = default;

public:
  explicit Add(Children inChildren);

public:
  const FunctionDeclaration &getDeclaration() const noexcept override;

  std::unique_ptr<Function> makeFunction(Children children) const override;
};

}
