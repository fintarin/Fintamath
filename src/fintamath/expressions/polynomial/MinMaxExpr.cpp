#include "fintamath/expressions/polynomial/MinMaxExpr.hpp"

#include <utility>

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(MinMaxExpr)

MinMaxExpr::MinMaxExpr(const IFunction &inFunc, ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(inFunc, std::move(inChildren)) {
}

}
