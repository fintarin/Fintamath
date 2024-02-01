#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/E.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Exp::call(const ArgumentRefVector &argVect) const {
  static const E lhs;
  const auto &rhs = argVect.front().get();

  return Pow{}(lhs, rhs);
}

}
