#include "fintamath/functions/other/Deg.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Deg::call(const ArgumentRefVector &argVect) const {
  static const ArgumentPtr degVal = divExpr(Pi(), Integer(180));
  const auto &rhs = argVect.front().get();

  return mulExpr(rhs, *degVal)->toMinimalObject();
}

}
