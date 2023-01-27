#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp" // TODO: remove this include
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

// TODO: remove this, and don't use Expression in IExpression
std::string IExpression::tryPutInBracketsIfNeg(const MathObjectPtr &obj) {
  if (const auto *expr = cast<Expression>(obj.get()); expr && cast<Neg>(expr->getInfo().get())) {
    return "(" + expr->toString() + ")";
  }

  return obj->toString();
}

void IExpression::validateFunctionArgs(const IFunction &func, const ArgumentsVector &args) const {
  ArgumentsVector nonMatchingArgs = func.getNonMatchingArgs(args);

  for (const auto &arg : nonMatchingArgs) {
    if (!cast<IExpression>(&arg.get()) && !cast<Variable>(&arg.get()) && !cast<IConstant>(&arg.get())) {
      throw InvalidInputException(toString());
    }
  }
}

}
