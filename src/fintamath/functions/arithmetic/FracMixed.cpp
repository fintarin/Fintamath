#include "fintamath/functions/arithmetic/FracMixed.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> FracMixed::call(const ArgumentRefVector &argsVect) const {
  const auto &integ = cast<IArithmetic>(argsVect[0].get());
  const auto &numer = cast<IArithmetic>(argsVect[1].get());
  const auto &denom = cast<IArithmetic>(argsVect[2].get());

  return Add()(integ, *Div()(numer, denom));
}

}
