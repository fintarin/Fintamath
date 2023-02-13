#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

const std::function<MathObjectPtr(const IFunction &function, ArgumentsPtrVector &&args)>
    IFunction::buildFunctionExpression = &Expression::buildFunctionExpression;

}
