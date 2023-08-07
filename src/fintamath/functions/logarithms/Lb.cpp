#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/functions/logarithms/Log.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Lb::call(const ArgumentsRefVector &argsVect) const {
  static const Integer lhs = 2;
  const auto &rhs = argsVect.front().get();

  return Log()(lhs, rhs);
}

}
