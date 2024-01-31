#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Index::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Variable>(argVect.front().get());
  const auto &rhs = cast<Integer>(argVect.back().get());

  return Variable(lhs.toString(), rhs).clone();
}

}
