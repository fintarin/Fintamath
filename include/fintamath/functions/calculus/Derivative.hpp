#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Derivative final : public IFunctionCRTP<IComparable, Derivative, IComparable, Variable> {
public:
  Derivative() : IFunctionCRTP(false) {
  }

  std::string toString() const override {
    return "derivative";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Derivative;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Derivative, derivativeExpr);

}
