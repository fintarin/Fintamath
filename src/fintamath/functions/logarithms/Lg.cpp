#include "fintamath/functions/logarithms/Lg.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Lg)

std::unique_ptr<IMathObject> Lg::call(const ArgumentRefVector &argVect) const {
  static const Integer lhs = 10;
  const auto &rhs = argVect.front().get();

  return Log{}(lhs, rhs);
}

}
