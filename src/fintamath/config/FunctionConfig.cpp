#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

const std::function<std::unique_ptr<IMathObject>(const IFunction &function, const ArgumentsRefVector &args)>
    IFunction::makeFunctionExpression = [](const IFunction &function, const ArgumentsRefVector &args) {
      return Expression::makeFunctionExpression(function, args);
    };

}
