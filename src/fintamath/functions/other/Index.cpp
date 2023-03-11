#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Index::call(const ArgumentsVector &argsVect) const {
  return makeFunctionExpression(*this, toArgumentsPtrVect(argsVect));
}

}
