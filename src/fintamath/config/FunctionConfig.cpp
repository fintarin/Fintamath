#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> IFunction::makeFunctionExpression(const IFunction &function,
                                                               const ArgumentsRefVector &args) {
  return fintamath::makeFunctionExpression(function, args);
}

std::unique_ptr<IMathObject> IFunction::makeRawFunctionExpression(const IFunction &function,
                                                                  const ArgumentsRefVector &args) {
  return fintamath::makeRawFunctionExpression(function, args);
}

}
