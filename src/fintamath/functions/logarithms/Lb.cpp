#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/functions/logarithms/Log.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Lb::call(const ArgumentRefVector &argVect) const {
  static const Integer lhs = 2;
  const auto &rhs = argVect.front().get();

  return Log{}(lhs, rhs);
}

}
