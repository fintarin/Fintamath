#pragma once

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/expressions/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Add : public IFunction {
  FINTAMATH_CLASS_BODY(Add, IFunction)

protected:
  Add() = default;

public:
  explicit Add(Children inChildren);

public:
  constexpr FunctionDeclaration getFunctionDeclaration() const noexcept override;

  std::unique_ptr<IFunction> makeFunction(Children children) const override;
};

constexpr Add::FunctionDeclaration Add::getFunctionDeclaration() const noexcept {
  constexpr MathObjectClass numberClass = INumber::getClassStatic();
  return {
    .expressionDeclarion = {
      .domainAndRangeVariants = {{
        .returnClass = numberClass,
        .childClasses = {numberClass, numberClass},
      }}
    },
    .functionName = "add",
  };
}

}
