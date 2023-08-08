#include "fintamath/expressions/unary/InvHyperbolicExpression.hpp"

namespace fintamath {

InvHyperbolicExpression::InvHyperbolicExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

}
