#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Log final : public IFunctionCRTP<INumber, Log, INumber, INumber> {
public:
  std::string toString() const override {
    return "log";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Log;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

  static std::unique_ptr<IMathObject> multiLogSimplify(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> logSimplify(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> logSimplify(const Rational &lhs, const Rational &rhs);

  static std::unique_ptr<IMathObject> logSimplify(const Real &lhs, const Real &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Log, logExpr);

}
