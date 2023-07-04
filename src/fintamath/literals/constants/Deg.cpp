#include "fintamath/literals/constants/Deg.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Deg::call() const {
  static std::unique_ptr<IMathObject> res = makeExpr(Div(), Pi(), Integer(180));
  return res->clone();
}

}
