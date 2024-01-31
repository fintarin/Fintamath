#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Not::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<Boolean>(argVect.front().get());

  return Boolean(!rhs).clone();
}

}
