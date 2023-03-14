#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

unique_ptr<IMathObject> Div::call(const ArgumentsRefVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) / cast<IArithmetic>(argsVect.back().get());
}

}
