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

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
