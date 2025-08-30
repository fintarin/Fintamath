#pragma once

#include "fintamath/expressions/ExpressionBase.hpp"
#include "fintamath/expressions/functions/Function.hpp"

namespace fintamath {

class AddOper : public Function {
  FINTAMATH_CLASS_BODY(AddOper, Function)

protected:
  AddOper() = default;

public:
  const FunctionDeclaration &getDeclaration() const noexcept override;

  std::unique_ptr<Function> makeFunction(Children children) const override;
};

}
