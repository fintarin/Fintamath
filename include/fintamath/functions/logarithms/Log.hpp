#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Log : public IFunctionCRTP<INumber, Log, INumber, INumber> {
public:
  Log() = default;

  std::string toString() const override {
    return "log";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
