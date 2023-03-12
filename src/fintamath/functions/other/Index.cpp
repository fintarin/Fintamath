#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Index::call(const ArgumentsRefVector &argsVect) const {
  return makeFunctionExpression(*this, argsVect);
}

}
