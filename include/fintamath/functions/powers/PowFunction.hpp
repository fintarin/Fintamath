#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class PowFunction final : public IFunctionCRTP<IArithmetic, PowFunction, IArithmetic, IArithmetic> {
public:
  std::string toString() const override {
    return "pow";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::PowFunction, "PowFunction"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
