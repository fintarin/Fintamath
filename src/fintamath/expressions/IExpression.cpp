#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"
#include <memory>

namespace fintamath {

void IExpression::validateArgs(const IFunction &func, const ArgumentsPtrVector &args) const {
  const ArgumentsTypesVector argsTypes = func.getArgsTypes();

  if (argsTypes.size() != args.size()) {
    throw InvalidInputException(toString());
  }

  for (size_t i = 0; i < args.size(); i++) {
    const std::shared_ptr<IMathObject> &child = args[i];
    const std::type_info &type = argsTypes[i];

    if (is<Variable>(child)) {
      continue;
    }

    if (const auto childConst = cast<IConstant>(child)) {
      const std::type_info &childType = childConst->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }

      continue;
    }

    if (const auto childExpr = cast<IExpression>(child)) {
      std::shared_ptr<IFunction> childFunc = childExpr->getFunction();

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

void IExpression::simplifyExpr(std::shared_ptr<IMathObject> &obj) {
  if (const auto exprObj = cast<IExpression>(obj)) {
    if (const auto simplObj = exprObj->simplify()) {
      obj = simplObj;
    }
  }
}

void IExpression::setMathObjectPrecision(std::shared_ptr<IMathObject> &obj, uint8_t precision) {
  if (is<INumber>(obj)) {
    obj = std::make_shared<Real>(convert<Real>(*obj).precise(precision));
    return;
  }

  if (auto expr = cast<IExpression>(obj)) {
    expr->setPrecision(precision);
    return;
  }
}

}
