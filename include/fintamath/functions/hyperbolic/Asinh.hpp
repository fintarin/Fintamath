#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Asinh : public IFunctionCRTP<INumber, Asinh, INumber> {
public:
  Asinh() = default;

  std::string toString() const override {
    return "asinh";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Asinh);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAsinhSimpl(const INumber &rhs);
};

}
