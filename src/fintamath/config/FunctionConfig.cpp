#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

const std::function<std::unique_ptr<IMathObject>(const IFunction &function, ArgumentsPtrVector &&args)>
    IFunction::makeFunctionExpression = &Expression::makeFunctionExpression;

}
