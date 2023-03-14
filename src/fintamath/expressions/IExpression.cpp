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

ArgumentsPtrVector IExpression::getVariables() const {
  return {};
}

void IExpression::validateChildren(const IFunction &func, const ArgumentsPtrVector &children) const {
  const ArgumentsTypesVector childrenTypes = func.getArgsTypes();

  if (childrenTypes.size() != children.size()) {
    throw InvalidInputException(toString());
  }

  for (size_t i = 0; i < children.size(); i++) {
    const std::shared_ptr<IMathObject> &child = children[i];
    const std::type_info &type = childrenTypes[i];

    if (const auto childExpr = cast<IExpression>(child)) {
      const std::shared_ptr<IFunction> childFunc = childExpr->getFunction();
      const std::type_info &childType = childFunc->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType) && !InheritanceTable::isBaseOf(childType, type)) {
        throw InvalidInputException(toString());
      }
    }
    else if (const auto childConst = cast<IConstant>(child)) {
      const std::type_info &childType = childConst->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }
    }
    else if (!is<Variable>(child) && !InheritanceTable::isBaseOf(type, typeid(*child))) {
      throw InvalidInputException(toString());
    }
  }
}

void IExpression::compressChild(std::shared_ptr<IMathObject> &child) {
  if (const auto expr = cast<IExpression>(child); expr && !expr->getFunction()) {
    child = expr->getChildren().front();
  }
}

void IExpression::simplifyChild(std::shared_ptr<IMathObject> &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->simplify()) {
      child = simplObj;
    }
  }
  else if (const auto constChild = cast<IConstant>(child)) {
    std::shared_ptr<IMathObject> constVal = (*constChild)();

    if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise()) {
      child = constChild;
    }
    else {
      child = constVal;
    }
  }
}

// void IExpression::setMathObjectPrecision(std::shared_ptr<IMathObject> &obj, uint8_t precision) {
//   if (is<INumber>(obj)) {
//     obj = std::make_shared<Real>(convert<Real>(*obj).precise(precision));
//     return;
//   }

//   if (auto expr = cast<IExpression>(obj)) {
//     expr->setPrecision(precision);
//     return;
//   }
// }

}
