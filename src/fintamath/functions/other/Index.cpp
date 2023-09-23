#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Index::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = cast<Variable>(argsVect.front().get());
  const auto &rhs = cast<Integer>(argsVect.back().get());

  return Variable(lhs.toString(), rhs).clone();
}

}
