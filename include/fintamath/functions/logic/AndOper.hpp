#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class AndOper : public IOperatorCRTP<Boolean, AndOper, Boolean, Boolean> {
  FINTAMATH_CLASS_BODY(AndOper, IOperator)

public:
  std::string toString() const override {
    return "&";
  }

  static constexpr bool isAssociativeStatic() noexcept {
    return true;
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::Conjunction;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
