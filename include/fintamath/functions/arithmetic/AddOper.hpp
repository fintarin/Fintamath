#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class AddOper : public IOperator {
  FINTAMATH_CLASS_BODY(AddOper, IOperator)

public:
  const OperatorDeclaration &getOperatorDeclaration() const noexcept override;

  std::unique_ptr<IFunction> makeFunctionSelf(Arguments inArgs) const override;

private:
  static const OperatorDeclaration addOperDeclaration;
};

}
