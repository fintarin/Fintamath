#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Acosh : public IFunctionCRTP<Acosh, INumber> {
public:
  Acosh() = default;

  std::string toString() const override {
    return "acosh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
