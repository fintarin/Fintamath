#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class AddOper : public IOperatorCRTP<IArithmetic, AddOper, IArithmetic, IArithmetic> {
  FINTAMATH_CLASS_BODY(AddOper, IOperator)

public:
  std::string toString() const override {
    return "+";
  }

  static constexpr bool isAssociativeStatic() {
    return true;
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Addition;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
