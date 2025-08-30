#pragma once

#include "fintamath/functions/FunctionClassBody.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Add;

class AddOper : public IOperator {
  FINTAMATH_FUNCTION_CLASS_BODY(AddOper, IOperator)

public:
  const OperatorDeclaration &getOperatorDeclaration() const noexcept override;

  static std::unique_ptr<Add> make(Arguments inArgs);

private:
  static const OperatorDeclaration addOperDeclaration;
};

}
