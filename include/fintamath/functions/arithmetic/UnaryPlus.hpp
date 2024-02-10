#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus final : public IOperatorCRTP<IArithmetic, UnaryPlus, IArithmetic> {
public:
  UnaryPlus() : IOperatorCRTP(Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "+";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::UnaryPlus;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
