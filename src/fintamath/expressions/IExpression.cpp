#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

std::string IExpression::tryPutInBracketsIfNeg(const MathObjectPtr &obj) {
  if (!obj->instanceOf<Expression>()) {
    return obj->toString();
  }

  const auto &exprObj = obj->to<Expression>();

  if (exprObj.getInfo()->instanceOf<Neg>()) {
    return "(" + exprObj.toString() + ")";
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

MathObjectPtr IExpression::simplify() const {
  return simplify(false);
}

std::vector<MathObjectPtr> IExpression::getVariables() const {
  return {};
}

}
