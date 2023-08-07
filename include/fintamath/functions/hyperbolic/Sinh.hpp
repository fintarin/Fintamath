#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sinh : public IFunctionCRTP<INumber, Sinh, INumber> {
public:
  Sinh() = default;

  std::string toString() const override {
    return "sinh";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Sinh);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSinhSimpl(const INumber &rhs);
};

}
