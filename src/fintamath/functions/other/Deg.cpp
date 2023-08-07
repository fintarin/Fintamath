#include "fintamath/functions/other/Deg.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Deg::call(const ArgumentsRefVector &argsVect) const {
  static const ArgumentPtr degVal = makeExpr(Div(), Pi(), Integer(180));
  const auto &rhs = argsVect.front().get();

  return makeExpr(Mul(), rhs, *degVal)->toMinimalObject();
}

}
