#pragma once

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/expressions/ExpressionBase.hpp"
#include "fintamath/expressions/functions/Function.hpp"
#include "fintamath/numbers/Number.hpp"

namespace fintamath {

class Add : public Function {
  FINTAMATH_CLASS_BODY(Add, Function)

protected:
  Add() = default;

public:
  explicit Add(Children inChildren);

public:
  constexpr FunctionDeclaration getFunctionDeclaration() const noexcept override {
    constexpr MathObjectClass numberClass = Number::getClassStatic();
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

  std::unique_ptr<Function> makeFunction(Children children) const override;
};

}
