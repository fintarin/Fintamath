#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

namespace fintamath {

const function<unique_ptr<IMathObject>(const IFunction &function, const ArgumentsRefVector &args)>
    IFunction::makeFunctionExpression = [](const IFunction &function, const ArgumentsRefVector &args) {
      return fintamath::makeFunctionExpression(function, args);
    };

}
