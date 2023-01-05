#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Acos : public IFunctionCRTP<Acos, INumber> {
public:
  Acos() = default;

  std::string toString() const override {
    return "acos";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
