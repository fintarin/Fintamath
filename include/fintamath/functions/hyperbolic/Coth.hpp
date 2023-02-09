#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Coth : public IFunctionCRTP<INumber, Coth, INumber> {
public:
  Coth() = default;

  std::string toString() const override {
    return "coth";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
