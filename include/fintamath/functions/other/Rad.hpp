#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Rad : public IFunctionCRTP<INumber, Rad, INumber> {
public:
  Rad() = default;

  std::string toString() const override {
    return "rad";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Rad;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
