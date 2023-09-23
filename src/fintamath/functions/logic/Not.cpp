#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Not::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<Boolean>(argsVect.front().get());

  return Boolean(!rhs).clone();
}

}
