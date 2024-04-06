#pragma once

#include <map>
#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer;
class Rational;
class Real;

class Root : public IFunctionCRTP<INumber, Root, INumber, INumber> {
  FINTAMATH_CLASS_BODY(Root, IFunction)

  using RootToFactorMap = std::map<Integer, Integer>;

public:
  std::string toString() const override {
    return "root";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiRootSimplify(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> rootSimplify(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> rootSimplify(const Rational &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> rootSimplify(const Real &lhs, const Integer &rhs);

  static RootToFactorMap roots(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> perfectRoot(const Integer &lhs, const Integer &rhs);

  static Integer extractFirstFactor(RootToFactorMap &rootToFactorMap);
};

FINTAMATH_FUNCTION_EXPRESSION(Root, rootExpr);

}
