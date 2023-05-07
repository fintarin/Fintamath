#include "fintamath/expressions/polynomial/MinMaxExpression.hpp"

namespace fintamath {

MinMaxExpression::MinMaxExpression(const IFunction &inFunc, const ArgumentsPtrVector &inChildren)
    : IPolynomExpressionCRTP(inFunc, inChildren) {
}

}
