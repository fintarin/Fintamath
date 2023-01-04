#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

const std::function<MathObjectPtr(const IFunction &function, const ArgumentsVector &args)>
    IFunction::buildFunctionExpression = &Expression::buildFunctionExpression;

}
