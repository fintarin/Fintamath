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
  constexpr const FunctionDeclaration &getFunctionDeclaration() const noexcept override {
    return addDeclaration;
  }

  std::unique_ptr<IFunction> makeFunction(Children children) const override;

private:
  FINTAMATH_EXPORT static const FunctionDeclaration addDeclaration;
};

}
