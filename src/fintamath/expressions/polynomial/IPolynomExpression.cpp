#include "fintamath/expressions/IPolynomExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

std::shared_ptr<IFunction> IPolynomExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IPolynomExpression::getChildren() const {
  return children;
}

std::string IPolynomExpression::toString() const {
  std::string result;

  result += childToString(children.front(), {});

  for (size_t i = 1; i < children.size(); i++) {
    result += childToString(children[i], children[i - 1]);
  }

  return result;
}

ArgumentPtr IPolynomExpression::simplify() const {
  ArgumentPtr simpl = cast<IPolynomExpression>(clone());

  preSimplifyChild(simpl);
  postSimplifyChild(simpl);

  if (auto simplExpr = cast<IPolynomExpression>(simpl->clone()); simplExpr && simplExpr->children.size() == 1) {
    return simplExpr->children.front();
  }

  return simpl;
}

ArgumentPtr IPolynomExpression::preSimplifyChildren(size_t /*lhsChildNum*/, size_t /*rhsChildNum*/) const {
  return {};
}

ArgumentPtr IPolynomExpression::postSimplifyChildren(size_t /*lhsChildNum*/, size_t /*rhsChildNum*/) const {
  return {};
}

void IPolynomExpression::preSimplifyRec() {
  size_t childrenSize = children.size();

  for (size_t i = 1; i < children.size(); i++) {
    if (auto res = preSimplifyChildren(i - 1, i)) {
      children[i - 1] = res;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
  }

  if (children.size() != childrenSize) {
    preSimplifyRec();
  }
}

void IPolynomExpression::postSimplifyRec() {
  size_t childrenSize = children.size();

  for (size_t i = 1; i < children.size(); i++) {
    if (ArgumentPtr callFuncRes = callFunction(*func, {children[i - 1], children[i]})) {
      children[i - 1] = callFuncRes;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
    else if (ArgumentPtr simplRes = postSimplifyChildren(i - 1, i)) {
      children[i - 1] = simplRes;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
  }

  if (children.size() != childrenSize) {
    postSimplifyRec();
  }
}

void IPolynomExpression::globalSimplifyRec() {
  size_t childrenSize = children.size();
  const SimplifyFunctionsVector functions = getFunctionsForSimplify();

  for (size_t i = 1; i < children.size(); i++) {
    const ArgumentPtr &lhsChild = children[i - 1];
    const ArgumentPtr &rhsChild = children[i];

    if (auto callFuncRes = callFunction(*func, {lhsChild, rhsChild})) {
      children[i - 1] = callFuncRes;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
    else if (auto simplRes = useSimplifyFunctions(functions, lhsChild, rhsChild)) {
      children[i - 1] = simplRes;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
  }

  if (children.size() != childrenSize) {
    globalSimplifyRec();
  }
}

ArgumentPtr IPolynomExpression::useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs, const ArgumentPtr &lhs,
                                                     const ArgumentPtr &rhs) {
  for (const auto &func : simplFuncs) {
    if (auto res = func(lhs, rhs)) {
      return res;
    }
  }

  return {};
}

ArgumentPtr IPolynomExpression::preSimplify() const {
  auto simpl = cast<IPolynomExpression>(clone());

  {
    ArgumentsPtrVector oldChildren = simpl->children;
    simpl->children.clear();

    for (auto &child : oldChildren) {
      preSimplifyChild(child);
      simpl->addElement(child);
    }
  }

  simpl->sort();
  simpl->preSimplifyRec();
  simpl->globalSimplifyRec();

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

ArgumentPtr IPolynomExpression::postSimplify() const {
  auto simpl = cast<IPolynomExpression>(clone());

  {
    ArgumentsPtrVector oldChildren = simpl->children;
    simpl->children.clear();

    for (auto &child : oldChildren) {
      postSimplifyChild(child);
      simpl->addElement(child);
    }
  }

  simpl->sort();
  simpl->postSimplifyRec();
  simpl->globalSimplifyRec();

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

IPolynomExpression::SimplifyFunctionsVector IPolynomExpression::getFunctionsForSimplify() const {
  return {};
}

bool IPolynomExpression::isTermsOrderInversed() const {
  return false;
}

bool IPolynomExpression::isComparableOrderInversed() const {
  return false;
}

bool IPolynomExpression::isUnaryOperatorsOrderInversed() const {
  return false;
}

void IPolynomExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.empty()) {
    throw InvalidInputFunctionException(toString(), {});
  }

  children = childVect;
}

void IPolynomExpression::sort() {
  std::sort(children.begin(), children.end(), [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return comparator(lhs, rhs) < 0;
  });
}

int IPolynomExpression::comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr && !rhsExpr) {
    return comparatorNonExpressions(lhs, rhs);
  }

  if (int res = comparatorPolynomsAndBinaryFunctions(lhs, rhs); res != 0) {
    return res;
  }

  if (int res = comparatorChildren(lhsExpr, rhsExpr); res != 0) {
    return res;
  }

  if (int res = comparatorExpressionAndNonExpression(lhs, rhs); res != 0) {
    return res;
  }

  return comparatorFunctions(lhsExpr, rhsExpr);
}

int IPolynomExpression::comparatorPolynomsAndBinaryFunctions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr && rhsExpr && !is<IPolynomExpression>(lhsExpr) && !is<IPolynomExpression>(rhsExpr) &&
      lhsExpr->getFunction()->getFunctionType() == IFunction::Type::Binary &&
      rhsExpr->getFunction()->getFunctionType() == IFunction::Type::Binary) {
    {
      std::vector<Variable> lhsVars = getVariables(lhsExpr->getChildren().front());
      std::vector<Variable> rhsVars = getVariables(rhsExpr->getChildren().front());

      if (auto res = comparatorVariables(lhsVars, rhsVars, false); res != 0) {
        return res;
      }
    }

    {
      std::vector<Variable> lhsVars = getVariables(lhsExpr->getChildren().back());
      std::vector<Variable> rhsVars = getVariables(rhsExpr->getChildren().back());

      if (auto res = comparatorVariables(lhsVars, rhsVars, false); res != 0) {
        return res;
      }
    }
  }
  else if (lhsExpr && rhsExpr && (is<IPolynomExpression>(lhsExpr) || is<IPolynomExpression>(rhsExpr))) {
    if (int res = comparatorChildren(lhs, rhs, true); res != 0) {
      return res;
    }
  }

  std::vector<Variable> lhsVars = getVariables(lhs);
  std::vector<Variable> rhsVars = getVariables(rhs);

  if (int res = comparatorVariables(lhsVars, rhsVars, isTermsOrderInversed()); res != 0) {
    return res;
  }

  return 0;
}

int IPolynomExpression::comparatorFunctions(const std::shared_ptr<const IExpression> &lhsExpr,
                                            const std::shared_ptr<const IExpression> &rhsExpr) const {

  if (!lhsExpr || !rhsExpr) {
    return 0;
  }

  auto lhsFunc = lhsExpr->getFunction();
  auto rhsFunc = rhsExpr->getFunction();

  ArgumentsPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

  {
    ArgumentPtr lhsToCompare = nullptr;
    ArgumentPtr rhsToCompare = nullptr;

    if (lhsChildren.size() == 1) {
      lhsToCompare = lhsChildren.front();
    }
    if (rhsChildren.size() == 1) {
      rhsToCompare = rhsChildren.front();
    }

    if (lhsToCompare || rhsToCompare) {
      if (!lhsToCompare) {
        lhsToCompare = lhsExpr;
      }
      else if (!rhsToCompare) {
        rhsToCompare = rhsExpr;
      }

      if (int res = comparator(lhsToCompare, rhsToCompare); res != 0) {
        return res;
      }
    }
    else if (*lhsFunc == *rhsFunc) {
      return comparatorChildren(lhsChildren, rhsChildren);
    }
  }

  if (auto lhsOper = cast<IOperator>(lhsFunc)) {
    if (auto rhsOper = cast<IOperator>(rhsFunc)) {
      IOperator::Priority lhsPriority = lhsOper->getOperatorPriority();
      IOperator::Priority rhsPriority = rhsOper->getOperatorPriority();

      if (lhsPriority == rhsPriority) {
        if (auto res = comparatorChildren(lhsChildren, rhsChildren)) {
          return res;
        }
      }
      else {
        ArgumentPtr childToCompare;
        ArgumentsPtrVector childrenToCompare;
        bool isResInverted = false;

        if (lhsPriority > rhsPriority) {
          childToCompare = rhsExpr;
          childrenToCompare = lhsChildren;
        }
        else {
          childToCompare = lhsExpr;
          childrenToCompare = rhsChildren;
          isResInverted = true;
        }

        for (const auto &lhsChild : childrenToCompare) {
          if (auto res = comparator(lhsChild, childToCompare)) {
            return isResInverted ? res * -1 : res;
          }
        }
      }
    }
  }

  if (is<IOperator>(lhsFunc) && !is<IOperator>(rhsFunc)) {
    return -1;
  }
  if (!is<IOperator>(lhsFunc) && is<IOperator>(rhsFunc)) {
    return 1;
  }

  return lhsFunc->toString() < rhsFunc->toString() ? -1 : 1;
}

int IPolynomExpression::comparatorExpressionAndNonExpression(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr && !rhsExpr) {
    if (auto oper = cast<IOperator>(lhsExpr->getFunction());
        oper && oper->getOperatorPriority() <= IOperator::Priority::PrefixUnary &&
        !is<IExpression>(lhsExpr->getChildren().front())) {

      return isTermsOrderInversed() ? -1 : 1;
    }

    return !isTermsOrderInversed() ? -1 : 1;
  }

  if (!lhsExpr && rhsExpr) {
    if (auto oper = cast<IOperator>(rhsExpr->getFunction());
        oper && oper->getOperatorPriority() <= IOperator::Priority::PrefixUnary &&
        !is<IExpression>(rhsExpr->getChildren().front())) {

      return !isTermsOrderInversed() ? -1 : 1;
    }

    return isTermsOrderInversed() ? -1 : 1;
  }

  return 0;
}

int IPolynomExpression::comparatorNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  if (*lhs == *rhs) {
    return 0;
  }

  if (auto lhsComp = cast<IComparable>(lhs)) {
    if (auto rhsComp = cast<IComparable>(rhs)) {
      if (isComparableOrderInversed()) {
        return *lhsComp < *rhsComp ? -1 : 1;
      }

      return *lhsComp > *rhsComp ? -1 : 1;
    }
  }

  return lhs->toString() < rhs->toString() ? -1 : 1;
}

int IPolynomExpression::comparatorChildren(const ArgumentPtr &lhs, const ArgumentPtr &rhs,
                                           bool ignoreUnaryIfPossible) const {
  const std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr || !rhsExpr) {
    return 0;
  }

  ArgumentsPtrVector lhsChildren;

  if (is<IPolynomExpression>(lhsExpr)) {
    lhsChildren = lhsExpr->getChildren();
  }
  else if (const auto firstPolynomChild = findFirstPolynomChild(lhs)) {
    lhsChildren = {firstPolynomChild};
  }
  else {
    lhsChildren = {lhs};
  }

  ArgumentsPtrVector rhsChildren;

  if (is<IPolynomExpression>(rhsExpr)) {
    rhsChildren = rhsExpr->getChildren();
  }
  else if (const auto firstPolynomChild = findFirstPolynomChild(rhs)) {
    rhsChildren = {firstPolynomChild};
  }
  else {
    rhsChildren = {rhs};
  }

  if (lhsChildren.size() > 1 || rhsChildren.size() > 1) {
    if (int res = comparatorChildren(lhsChildren, rhsChildren, ignoreUnaryIfPossible); res != 0) {
      return res;
    }
  }

  return 0;
}

int IPolynomExpression::comparatorChildren(const ArgumentsPtrVector &lhsChildren, const ArgumentsPtrVector &rhsChildren,
                                           bool ignoreUnaryIfPossible) const {

  size_t lhsStart = 0;
  for (; lhsStart < lhsChildren.size(); lhsStart++) {
    if (is<Variable>(lhsChildren[lhsStart])) {
      break;
    }
    if (auto lhsChildExpr = cast<IExpression>(lhsChildren[lhsStart]); lhsChildExpr && hasVariables(lhsChildExpr)) {
      break;
    }
  }

  size_t rhsStart = 0;
  for (; rhsStart < rhsChildren.size(); rhsStart++) {
    if (is<Variable>(rhsChildren[rhsStart])) {
      break;
    }
    if (auto rhsChildExpr = cast<IExpression>(rhsChildren[rhsStart]); rhsChildExpr && hasVariables(rhsChildExpr)) {
      break;
    }
  }

  int unaryComparator = 0;

  for (size_t i = lhsStart, j = rhsStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    ArgumentPtr compLhs = lhsChildren[i];
    ArgumentPtr compRhs = rhsChildren[j];

    if (ignoreUnaryIfPossible) {
      bool isLhsUnary = false;

      if (const auto lhsExpr = cast<IExpression>(compLhs);
          lhsExpr && lhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {
        compLhs = lhsExpr->getChildren().front();
        isLhsUnary = true;
      }

      bool isRhsUnary = false;

      if (const auto rhsExpr = cast<IExpression>(compRhs);
          rhsExpr && rhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {
        compRhs = rhsExpr->getChildren().front();
        isRhsUnary = true;
      }

      if (unaryComparator == 0 && isLhsUnary != isRhsUnary) {
        unaryComparator = isLhsUnary ? -1 : 1;
      }
    }

    if (int res = comparator(compLhs, compRhs); res != 0) {
      return res;
    }
  }

  if (unaryComparator != 0 && lhsChildren.size() == rhsChildren.size()) {
    return !isUnaryOperatorsOrderInversed() ? unaryComparator : unaryComparator * -1;
  }

  for (size_t i = 0; i < std::min(lhsStart, rhsStart); i++) {
    if (int res = comparator(lhsChildren[i], rhsChildren[i]); res != 0) {
      return res;
    }
  }

  if (lhsChildren.size() == rhsChildren.size()) {
    return 0;
  }

  return lhsChildren.size() > rhsChildren.size() ? -1 : 1;
}

int IPolynomExpression::comparatorVariables(const std::vector<Variable> &lhsVars, const std::vector<Variable> &rhsVars,
                                            bool isTermsOrderInversed) {

  for (size_t i = 0; i < std::min(lhsVars.size(), rhsVars.size()); i++) {
    if (lhsVars[i] != rhsVars[i]) {
      return (lhsVars[i].toString() < rhsVars[i].toString()) ? -1 : 1;
    }
  }

  if (!lhsVars.empty() && rhsVars.empty()) {
    return !isTermsOrderInversed ? -1 : 1;
  }
  if (lhsVars.empty() && !rhsVars.empty()) {
    return isTermsOrderInversed ? -1 : 1;
  }

  return 0;
}

ArgumentPtr IPolynomExpression::findFirstPolynomChild(const ArgumentPtr &rhs) {
  auto res = cast<IExpression>(rhs);

  while (res && !is<IPolynomExpression>(res)) {
    res = cast<IExpression>(res->getChildren().front());
  }

  if (is<IPolynomExpression>(res)) {
    return res;
  }

  return {};
}

std::vector<Variable> IPolynomExpression::getVariables(const ArgumentPtr &rhs) {
  std::vector<Variable> vars;

  if (const auto &rhsExpr = cast<IExpression>(rhs)) {
    vars = rhsExpr->getVariablesUnsorted();
  }
  else if (auto var = cast<Variable>(rhs)) {
    vars = {*var};
  }

  return vars;
}

}
