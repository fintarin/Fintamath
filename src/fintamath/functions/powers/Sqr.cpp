#include "fintamath/functions/powers/Sqr.hpp"

#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqr::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = argsVect.front().get();
  static const Integer rhs = 2;

  return Pow()(lhs, rhs);
}

}
