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
  std::string toString() const override {
    return "+";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PrefixUnary;
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::UnaryPlus;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
