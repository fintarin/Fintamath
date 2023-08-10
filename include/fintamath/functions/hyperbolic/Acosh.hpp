#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Acosh : public IFunctionCRTP<INumber, Acosh, INumber> {
public:
  Acosh() = default;

  std::string toString() const override {
    return "acosh";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Acosh);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcoshSimplify(const INumber &rhs);

  static std::unique_ptr<IMathObject> acoshSimplify(const Real &rhs);
};

}
