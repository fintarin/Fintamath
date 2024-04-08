#include "fintamath/expressions/unary/InvHyperbExpr.hpp"

#include <utility>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(InvHyperbExpr)

InvHyperbExpr::InvHyperbExpr(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

}
