#include "fintamath/functions/logarithms/Lb.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Lb::call(const ArgumentRefVector &argVect) const {
  static const Integer lhs = 2;
  const auto &rhs = argVect.front().get();

  return Log{}(lhs, rhs);
}

}
