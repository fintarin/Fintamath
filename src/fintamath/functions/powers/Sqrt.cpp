#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqrt::call(const ArgumentsRefVector &argsVect) const {
  return Root()(argsVect.front().get(), Integer(2));
}

}
