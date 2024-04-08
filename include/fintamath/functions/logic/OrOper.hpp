#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class OrOper : public IOperatorCRTP<Boolean, OrOper, Boolean, Boolean> {
  FINTAMATH_CLASS_BODY(OrOper, IOperator)

public:
  std::string toString() const override {
    return "|";
  }

  static constexpr bool isAssociativeStatic() noexcept {
    return true;
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::Disjunction;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
