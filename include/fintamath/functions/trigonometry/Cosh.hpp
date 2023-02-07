#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Cosh : public IFunctionCRTP<Cosh, INumber> {
public:
  Cosh() = default;

  std::string toString() const override {
    return "cosh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
