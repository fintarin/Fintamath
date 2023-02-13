#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

MathObjectPtr Index::call(const ArgumentsVector &argsVect) const {
  return buildFunctionExpression(*this, argsVectToArgsPtrVect(argsVect));
}

}
