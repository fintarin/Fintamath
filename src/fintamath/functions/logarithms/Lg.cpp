#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/functions/logarithms/Log.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Lg::call(const ArgumentsRefVector &argsVect) const {
  static const Integer lhs = 10;
  const auto &rhs = argsVect.front().get();

  return Log()(lhs, rhs);
}

}
