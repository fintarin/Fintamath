#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Log : public IFunctionCRTP<Log, INumber, INumber> {
public:
  Log() = default;

  std::string toString() const override {
    return "log";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
