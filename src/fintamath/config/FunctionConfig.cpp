#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> IFunction::makeExprChecked(const IFunction &function, const ArgumentsRefVector &args) {
  return fintamath::makeExprChecked(function, args);
}

// TODO: uncomment
// std::unique_ptr<IMathObject> IFunction::makeExpr(const IFunction &function, const ArgumentsRefVector &args) {
//   return fintamath::makeExpr(function, args);
// }

}
