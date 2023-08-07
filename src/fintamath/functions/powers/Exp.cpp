#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/E.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Exp::call(const ArgumentsRefVector &argsVect) const {
  static const E lhs;
  const auto &rhs = argsVect.front().get();

  return Pow()(lhs, rhs);
}

}
