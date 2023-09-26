#include "fintamath/expressions/polynomial/MinMaxExpression.hpp"

namespace fintamath {

MinMaxExpression::MinMaxExpression(const IFunction &inFunc, ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(inFunc, std::move(inChildren)) {
}

}
