#include "fintamath/expressions/unary/InvHyperbExpression.hpp"

#include <utility>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

InvHyperbExpression::InvHyperbExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

}
