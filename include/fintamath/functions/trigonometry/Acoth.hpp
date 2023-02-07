#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Acoth : public IFunctionCRTP<Acoth, INumber> {
public:
  Acoth() = default;

  std::string toString() const override {
    return "acoth";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
