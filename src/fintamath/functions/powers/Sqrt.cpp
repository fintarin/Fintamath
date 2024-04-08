#include "fintamath/functions/powers/Sqrt.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Sqrt)

std::unique_ptr<IMathObject> Sqrt::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  static const Integer rhs = 2;

  return Root{}(lhs, rhs);
}

}
