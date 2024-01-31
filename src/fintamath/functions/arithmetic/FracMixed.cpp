#include "fintamath/functions/arithmetic/FracMixed.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> FracMixed::call(const ArgumentRefVector &argVect) const {
  const auto &integ = cast<IArithmetic>(argVect[0].get());
  const auto &numer = cast<IArithmetic>(argVect[1].get());
  const auto &denom = cast<IArithmetic>(argVect[2].get());

  return Add()(integ, *Div()(numer, denom));
}

}
