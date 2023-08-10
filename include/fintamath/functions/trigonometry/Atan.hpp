#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atan : public IFunctionCRTP<INumber, Atan, INumber> {
public:
  Atan() = default;

  std::string toString() const override {
    return "atan";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Atan);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAtanSimplify(const INumber &rhs);
};

}
