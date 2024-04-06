#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer;
class Rational;
class Real;
class Complex;

class Pow final : public IFunctionCRTP<INumber, Pow, INumber, INumber> {
  FINTAMATH_CLASS_BODY(Pow)

public:
  std::string toString() const override {
    return "pow";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiPowSimplify(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Rational &lhs, const Rational &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Real &lhs, const Real &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Complex &lhs, const Complex &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Pow, powExpr);

}
