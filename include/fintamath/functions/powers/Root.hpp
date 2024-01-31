#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer;
class Rational;
class Real;

class Root : public IFunctionCRTP<INumber, Root, INumber, INumber> {
public:
  Root() = default;

  std::string toString() const override {
    return "root";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Root;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiRootSimplify(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> rootSimplify(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> rootSimplify(const Rational &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> rootSimplify(const Real &lhs, const Integer &rhs);

  static std::map<Integer, Integer> roots(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> perfectRoot(const Integer &lhs, const Integer &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Root, rootExpr);

}
