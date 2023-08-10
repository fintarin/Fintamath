#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cos : public IFunctionCRTP<INumber, Cos, INumber> {
public:
  Cos() = default;

  std::string toString() const override {
    return "cos";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Cos);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCosSimplify(const INumber &rhs);
};

}
