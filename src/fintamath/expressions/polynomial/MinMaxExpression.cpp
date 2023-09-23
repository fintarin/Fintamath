#include "fintamath/expressions/polynomial/MinMaxExpression.hpp"

namespace fintamath {

MinMaxExpression::MinMaxExpression(const IFunction &inFunc, const ArgumentPtrVector &inChildren)
    : IPolynomExpressionCRTP(inFunc, inChildren) {
}

}
