#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Log : public IFunctionCRTP<INumber, Log, INumber, INumber> {
public:
  Log() = default;

  std::string toString() const override {
    return "log";
  }

  static MathObjectType getTypeStatic() {
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
