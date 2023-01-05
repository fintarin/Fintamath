#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Acot : public IFunctionCRTP<Acot, INumber> {
public:
  Acot() = default;

  std::string toString() const override {
    return "acot";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
