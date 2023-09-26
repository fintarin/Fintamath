#include "fintamath/expressions/unary/InvHyperbExpression.hpp"

namespace fintamath {

InvHyperbExpression::InvHyperbExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

}
