#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/expressions/functions/IFunction.hpp"

namespace fintamath {

class AddOper : public IFunction {
  FINTAMATH_CLASS_BODY(AddOper, IFunction)

protected:
  AddOper() = default;

public:
  constexpr const FunctionDeclaration &getFunctionDeclaration() const noexcept override {
    return addOperDeclaration;
  }

  std::unique_ptr<IFunction> makeFunction(Children children) const override;

private:
  FINTAMATH_EXPORT static const FunctionDeclaration addOperDeclaration;
};

}
