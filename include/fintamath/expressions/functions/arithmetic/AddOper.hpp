#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/expressions/functions/IOperator.hpp"

namespace fintamath {

class AddOper : public IOperator {
  FINTAMATH_CLASS_BODY(AddOper, IOperator)

public:
  constexpr const OperatorDeclaration &getOperatorDeclaration() const noexcept override {
    return addOperDeclaration;
  }

  std::unique_ptr<IFunction> makeFunction(Children children) const override;

private:
  FINTAMATH_EXPORT static const OperatorDeclaration addOperDeclaration;
};

}
