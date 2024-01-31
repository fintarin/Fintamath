#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/functions/logarithms/Log.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Lg::call(const ArgumentRefVector &argVect) const {
  static const Integer lhs = 10;
  const auto &rhs = argVect.front().get();

  return Log()(lhs, rhs);
}

}
