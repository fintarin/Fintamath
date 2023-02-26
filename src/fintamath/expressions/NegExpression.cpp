#include "fintamath/expressions/NegExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

MathObjectPtr NegExpression::simplify() const {
  return {};
}

MathObjectPtr NegExpression::simplify(bool isPrecise) const {
  return {};
}

std::string NegExpression::toString() const {
  std::string result = NEG.toString();
  if (const auto *child = cast<IExpression>(info.get())) {
    if (const auto *oper = cast<IOperator>(child->getFunction())) {
      if (auto priority = oper->getOperatorPriority(); priority != IOperator::Priority::PrefixUnary) {
        if (is<MulExpression>(child)) {
          return result + info->toString();
        }

        // TODO: refactor this when PowExpression will be implemented
        if (const auto *childExpr = cast<Expression>(child)) {
          if (is<Pow>(childExpr->getFunction())) {
            return result + info->toString();
          }
        }

        return result + putInBrackets(info->toString());
      }
    }
  }

  return result + info->toString();
}

const IFunction *NegExpression::getFunction() const {
  return &NEG;
}

}
