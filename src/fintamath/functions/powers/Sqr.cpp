#include "fintamath/functions/powers/Sqr.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqr::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  static const Integer rhs = 2;

  return Pow{}(lhs, rhs);
}

}
