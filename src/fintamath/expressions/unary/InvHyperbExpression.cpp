#include "fintamath/expressions/unary/InvHyperbExpression.hpp"

namespace fintamath {

InvHyperbExpression::InvHyperbExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

}
