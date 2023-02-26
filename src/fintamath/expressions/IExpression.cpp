#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp" // TODO: remove this include
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

void IExpression::validateArgs(const IFunction &func, const ArgumentsVector &args) const {
  const ArgumentsTypesVector argsTypes = func.getArgsTypes();

  if (argsTypes.size() != args.size()) {
    throw InvalidInputException(toString());
  }

  for (size_t i = 0; i < args.size(); i++) {
    const auto *child = &args[i].get();
    const auto &type = argsTypes[i];

    if (is<Variable>(child)) {
      continue;
    }

    if (const auto *childConst = cast<IConstant>(child)) {
      const std::type_info &childType = childConst->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }

      continue;
    }

    if (const auto *childExpr = cast<IExpression>(child)) {
      const auto *childFunc = childExpr->getFunction();

      if (!childFunc) {
        continue;
      }

      const std::type_info &childType = childFunc->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType) && !InheritanceTable::isBaseOf(childType, type)) {
        throw InvalidInputException(toString());
      }

      continue;
    }

    if (!InheritanceTable::isBaseOf(type, typeid(*child))) {
      throw InvalidInputException(toString());
    }
  }
}

std::string IExpression::putInBrackets(const std::string &str) const {
  return "(" + str + ")";
}

}
