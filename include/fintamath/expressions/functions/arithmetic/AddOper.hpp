#pragma once

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/expressions/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class AddOper : public IFunction {
  FINTAMATH_CLASS_BODY(AddOper, IFunction)

protected:
  AddOper() = default;

public:
  constexpr FunctionDeclaration getFunctionDeclaration() const noexcept override {
    constexpr MathObjectClass numberClass = INumber::getClassStatic();
    return {
      .expressionDeclarion = {
        .domainAndRangeVariants = {{
          .returnClass = numberClass,
          .childClasses = {numberClass, numberClass},
        }}
      },
      .functionName = "+",
    };
  }

  std::unique_ptr<IFunction> makeFunction(Children children) const override;
};

}
