#include "fintamath/expressions/polynomial/MinMaxExpression.hpp"

#include <utility>

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

MinMaxExpression::MinMaxExpression(const IFunction &inFunc, ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(inFunc, std::move(inChildren)) {
}

}
