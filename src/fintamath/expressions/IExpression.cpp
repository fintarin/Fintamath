#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp" // TODO: remove this include
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

// TODO: remove this, and don't use Expression in IExpression
std::string IExpression::tryPutInBracketsIfNeg(const MathObjectPtr &obj) {
  if (const auto *expr = cast<Expression>(obj.get()); expr && expr->getInfo()->instanceOf<Neg>()) {
    return "(" + expr->toString() + ")";
  }

  return obj->toString();
}

void IExpression::validateFunctionArgs(const IFunction &func, const ArgumentsVector &args) const {
  ArgumentsVector nonMatchingArgs = func.getNonMatchingArgs(args);

  for (const auto &arg : nonMatchingArgs) {
    if (!arg.get().instanceOf<Variable>() && !arg.get().instanceOf<IConstant>() &&
        !arg.get().instanceOf<IExpression>()) {
      throw InvalidInputException(toString());
    }
  }
}

}
