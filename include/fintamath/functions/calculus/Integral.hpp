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

class Integral final : public IFunctionCRTP<IComparable, Integral, IComparable, Variable> {
public:
  Integral() : IFunctionCRTP(false) {
  }

  std::string toString() const override {
    return "integral";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Integral;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Integral, integralExpr);

}
