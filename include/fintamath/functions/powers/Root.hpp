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

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Root);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiRootSimpl(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> rootSimpl(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> rootSimpl(const Rational &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> rootSimpl(const Real &lhs, const Integer &rhs);

  static std::map<Integer, Integer> roots(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> perfectRoot(const Integer &lhs, const Integer &rhs);
};

}
