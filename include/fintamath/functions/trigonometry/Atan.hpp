#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Atan : public IFunctionCRTP<Atan, INumber> {
public:
  Atan() = default;

  std::string toString() const override {
    return "atan";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
