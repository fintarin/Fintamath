#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

IPolynomExpression::IPolynomExpression(const IFunction &inFunc, ArgumentPtrVector args)
    : func(cast<IFunction>(inFunc.clone())),
      children(std::move(args)) {
}

const std::shared_ptr<IFunction> &IPolynomExpression::getFunction() const {
  return func;
}

const ArgumentPtrVector &IPolynomExpression::getChildren() const {
  return children;
}

std::string IPolynomExpression::toString() const {
  const auto oper = cast<IOperator>(func);
  if (!oper) {
    return functionToString(*func, children);
  }

  std::string result;

  result += childToString(*oper, children.front(), {});

  for (auto i : std::views::iota(1U, children.size())) {
    const std::string childStr = childToString(*oper, children[i], children[i - 1]);

    if (childStr.size() > 2 && childStr[0] == ' ' && std::isdigit(childStr[1]) && std::isdigit(result.back())) {
      result += Mul().toString() + childStr.substr(1);
    }
    else {
      result += childStr;
    }
  }

  return result;
}

void IPolynomExpression::compress() {
  size_t i = 0;

  while (i < children.size()) {
    auto &child = children[i];

    if (const auto childPolynom = cast<IPolynomExpression>(child); childPolynom && *childPolynom->func == *func) {
      std::swap(child, children.back());
      children.pop_back();

      children.insert(children.end(),
                      childPolynom->children.begin(),
                      childPolynom->children.end());
    }
    else {
      i++;
    }
  }
}

ArgumentPtr IPolynomExpression::preSimplify() const {
  auto simpl = cast<IPolynomExpression>(clone());

  simpl->simplifyChildren(false);
  simpl->simplifyRec(false);

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

ArgumentPtr IPolynomExpression::postSimplify() const {
  auto simpl = cast<IPolynomExpression>(clone());

  simpl->simplifyChildren(true);
  simpl->simplifyRec(true);

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

void IPolynomExpression::simplifyRec(bool isPostSimplify) {
  compress();
  sort();

  bool isSimplified = true;

  // TODO: refactor this loop
  for (size_t i = 1; i < children.size(); i++) {
    const ArgumentPtr &lhs = children[i - 1];
    const ArgumentPtr &rhs = children[i];

    if (auto res = simplifyUndefined(*func, lhs, rhs)) {
      children = {res};
      break;
    }

    ArgumentPtr res;
    bool isResSimplified = false;

    if (isPostSimplify) {
      res = callFunction(*func, {lhs, rhs});
      isResSimplified = res != nullptr;
    }

    if (!res) {
      res = !isPostSimplify ? useSimplifyFunctions(getFunctionsForPreSimplify(),
                                                   *func,
                                                   children[i - 1],
                                                   children[i])
                            : useSimplifyFunctions(getFunctionsForPostSimplify(),
                                                   *func,
                                                   children[i - 1],
                                                   children[i]);
    }

    if (!res) {
      continue;
    }

    if (!isResSimplified) {
      ArgumentPtr prevExpr = makeExpr(*getFunction(), lhs, rhs);

      if (isPostSimplify) {
        postSimplifyChild(res);
      }
      else {
        preSimplifyChild(res);
      }

      if (*prevExpr == *res) {
        continue;
      }
    }

    children.erase(children.begin() + ptrdiff_t(i) - 1);
    children.erase(children.begin() + ptrdiff_t(i) - 1);
    children.emplace_back(res);

    i--;
    isSimplified = false;
  }

  if (!isSimplified) {
    simplifyRec(isPostSimplify);
  }
}

void IPolynomExpression::simplifyChildren(bool isPostSimplify) {
  ArgumentPtrVector oldChildren = children;

  children.clear();

  for (auto &child : oldChildren) {
    if (isPostSimplify) {
      postSimplifyChild(child);
    }
    else {
      preSimplifyChild(child);
    }

    children.emplace_back(child);
  }
}

IPolynomExpression::SimplifyFunctionVector IPolynomExpression::getFunctionsForPreSimplify() const {
  return {};
}

IPolynomExpression::SimplifyFunctionVector IPolynomExpression::getFunctionsForPostSimplify() const {
  return {};
}

std::string IPolynomExpression::childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string childStr = operatorChildToString(oper, inChild);
  return prevChild ? (putInSpaces(func->toString()) + childStr) : childStr;
}

bool IPolynomExpression::isTermsOrderInversed() const {
  return false;
}

bool IPolynomExpression::isComparableOrderInversed() const {
  return false;
}

void IPolynomExpression::setChildren(const ArgumentPtrVector &childVect) {
  if (childVect.empty()) {
    throw InvalidInputFunctionException(toString(), {});
  }

  children = childVect;
}

void IPolynomExpression::sort() {
  std::ranges::stable_sort(children, [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return comparator(lhs, rhs) < 0;
  });
}

int IPolynomExpression::comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr && !rhsExpr) {
    return comparatorNonExpressions(lhs, rhs);
  }

  auto lhsPolynom = cast<IPolynomExpression>(lhsExpr);
  auto rhsPolynom = cast<IPolynomExpression>(rhsExpr);

  if (lhsPolynom && rhsPolynom) {
    return comparatorPolynoms(lhsPolynom, rhsPolynom);
  }

  if (lhsExpr && !rhsExpr) {
    return comparatorExpressionAndNonExpression(lhsExpr, rhs);
  }

  if (!lhsExpr && rhsExpr) {
    return comparatorExpressionAndNonExpression(rhsExpr, lhs) * -1;
  }

  if (lhsPolynom && !rhsPolynom) {
    return comparatorPolynomAndNonPolynom(lhsPolynom, rhs);
  }

  if (!lhsPolynom && rhsPolynom) {
    return comparatorPolynomAndNonPolynom(rhsPolynom, lhs) * -1;
  }

  return comparatorExpressions(lhsExpr, rhsExpr);
}

int IPolynomExpression::comparatorNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
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

int IPolynomExpression::comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                                           const std::shared_ptr<const IPolynomExpression> &rhs) const {

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), rhs->getChildren());

  if (childrenComp.postfix != 0) {
    return childrenComp.postfix;
  }
  if (childrenComp.postfixUnary != 0) {
    return childrenComp.postfixUnary;
  }
  if (childrenComp.size != 0) {
    return childrenComp.size;
  }
  if (childrenComp.prefixFirst != 0) {
    return childrenComp.prefixFirst;
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction());
}

int IPolynomExpression::comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                                       const ArgumentPtr &rhs) const {

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), {rhs});
  int res = -1;

  if (childrenComp.postfix != 0) {
    res = childrenComp.postfix;
  }
  else if (childrenComp.prefixFirst != 0) {
    res = childrenComp.prefixFirst;
  }

  return res * (isTermsOrderInversed() ? -1 : 1);
}

int IPolynomExpression::comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                                             const ArgumentPtr &rhs) const {

  if (!is<Variable>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }

  if (auto res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  if (auto lhsOper = cast<IOperator>(lhs->getFunction())) {
    auto lhsOperPriority = lhsOper->getOperatorPriority();

    switch (lhsOperPriority) {
      case IOperator::Priority::PostfixUnary:
      case IOperator::Priority::PrefixUnary: {
        if (int res = comparator(lhs->getChildren().front(), rhs); res != 0) {
          return res;
        }

        return 1;
      }
      case IOperator::Priority::Exponentiation:
      case IOperator::Priority::Multiplication: {
        ArgumentPtr rhsExpr = makeExpr(*lhsOper, rhs, Integer(1).clone());
        return comparator(lhs, rhsExpr) * (isTermsOrderInversed() ? -1 : 1);
      }
      default: {
        break;
      }
    }
  }

  return !isTermsOrderInversed() ? -1 : 1;
}

int IPolynomExpression::comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                                              const std::shared_ptr<const IExpression> &rhs) const {

  auto lhsOper = cast<IOperator>(lhs->getFunction());
  auto rhsOper = cast<IOperator>(rhs->getFunction());

  const ArgumentPtrVector &lhsChildren = lhs->getChildren();
  const ArgumentPtrVector &rhsChildren = rhs->getChildren();

  if (lhsOper &&
      lhsOper->getOperatorPriority() == IOperator::Priority::PrefixUnary &&
      (!rhsOper || rhsOper->getOperatorPriority() != IOperator::Priority::PrefixUnary)) {

    if (int res = comparator(lhsChildren.front(), rhs); res != 0) {
      return res;
    }
  }

  if (rhsOper &&
      rhsOper->getOperatorPriority() == IOperator::Priority::PrefixUnary &&
      (!lhsOper || lhsOper->getOperatorPriority() != IOperator::Priority::PrefixUnary)) {

    if (int res = comparator(lhs, rhsChildren.front()); res != 0) {
      return res;
    }
  }

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), rhs->getChildren());

  if (childrenComp.prefixVariables != 0) {
    return childrenComp.prefixVariables;
  }
  if (childrenComp.size != 0) {
    return childrenComp.size;
  }
  if (childrenComp.postfix != 0) {
    return childrenComp.postfix;
  }

  if (is<IOperator>(lhs->getFunction()) && is<IOperator>(rhs->getFunction())) {
    if (childrenComp.prefixLast != 0) {
      return childrenComp.prefixLast;
    }
  }
  else {
    if (childrenComp.prefixFirst != 0) {
      return childrenComp.prefixFirst;
    }
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction());
}

IPolynomExpression::ChildrenComparatorResult
IPolynomExpression::comparatorChildren(const ArgumentPtrVector &lhsChildren,
                                       const ArgumentPtrVector &rhsChildren) const {

  ChildrenComparatorResult result = {};

  size_t lhsStart = getPositionOfFirstChildWithVariable(lhsChildren);
  size_t rhsStart = getPositionOfFirstChildWithVariable(rhsChildren);

  for (size_t i = lhsStart, j = rhsStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    ArgumentPtr compLhs = lhsChildren[i];
    ArgumentPtr compRhs = rhsChildren[j];

    bool isLhsUnary = unwrapUnary(compLhs);
    bool isRhsUnary = unwrapUnary(compRhs);

    if (isLhsUnary && isRhsUnary) {
      compLhs = lhsChildren[i];
      compRhs = rhsChildren[j];
    }

    if (result.postfixUnary == 0 && isLhsUnary != isRhsUnary) {
      result.postfixUnary = !isLhsUnary ? -1 : 1;
    }

    if (result.postfix == 0) {
      result.postfix = comparator(compLhs, compRhs);
    }

    if (result.postfix != 0) {
      break;
    }
  }

  if (result.postfix == 0) {
    size_t lhsPostfixSize = lhsChildren.size() - lhsStart;
    size_t rhsPostfixSize = rhsChildren.size() - rhsStart;

    if (lhsPostfixSize != rhsPostfixSize) {
      result.postfix = lhsPostfixSize > rhsPostfixSize ? -1 : 1;
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.postfixUnary = 0;
  }

  for (auto end = std::min(std::max(lhsStart, rhsStart), std::min(lhsChildren.size(), rhsChildren.size()));
       auto i : std::views::iota(0U, end)) {

    int childrenComp = comparator(lhsChildren[i], rhsChildren[i]);

    if (childrenComp != 0) {
      result.prefixLast = childrenComp;
    }

    if (result.prefixFirst == 0) {
      result.prefixFirst = childrenComp;
    }

    if (result.prefixVariables == 0) {
      result.prefixVariables = comparatorVariables(lhsChildren[i], rhsChildren[i], false);
    }

    if (result.prefixVariables != 0 && result.prefixLast != 0) {
      break;
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.size = lhsChildren.size() > rhsChildren.size() ? -1 : 1;
  }

  return result;
}

int IPolynomExpression::comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                                            const std::shared_ptr<const IFunction> &rhs) {

  if (is<IOperator>(lhs) && !is<IOperator>(rhs)) {
    return -1;
  }
  if (!is<IOperator>(lhs) && is<IOperator>(rhs)) {
    return 1;
  }

  if (*lhs == *rhs) {
    return 0;
  }

  return lhs->toString() < rhs->toString() ? -1 : 1;
}

int IPolynomExpression::comparatorVariables(const ArgumentPtr &lhs, const ArgumentPtr &rhs, bool isTermsOrderInversed) const {
  ExpressionTreePathStack lhsPath;
  ExpressionTreePathStack rhsPath;

  std::shared_ptr<const Variable> lhsVar;
  std::shared_ptr<const Variable> rhsVar;

  if (const auto &expr = cast<IExpression>(lhs)) {
    lhsPath.emplace(expr, -1);
    lhsVar = getNextVariable(lhsPath);
  }
  else if (const auto &var = cast<Variable>(lhs)) {
    lhsVar = var;
  }

  if (const auto &expr = cast<IExpression>(rhs)) {
    rhsPath.emplace(expr, -1);
    rhsVar = getNextVariable(rhsPath);
  }
  else if (const auto &var = cast<Variable>(rhs)) {
    rhsVar = var;
  }

  if (lhsVar && !rhsVar) {
    return !isTermsOrderInversed ? -1 : 1;
  }

  if (!lhsVar && rhsVar) {
    return isTermsOrderInversed ? -1 : 1;
  }

  while (lhsVar && rhsVar) {
    if (int res = comparatorNonExpressions(lhsVar, rhsVar); res != 0) {
      return res;
    }

    lhsVar = getNextVariable(lhsPath);
    rhsVar = getNextVariable(rhsPath);
  }

  return 0;
}

std::shared_ptr<const Variable> IPolynomExpression::getNextVariable(ExpressionTreePathStack &stack) {
  while (!stack.empty()) {
    const ArgumentPtrVector &children = stack.top().first->getChildren();

    // TODO: looks weird
    size_t &exprIndex = stack.top().second;
    exprIndex++;

    bool hasExprChild = false;

    for (; exprIndex < children.size(); exprIndex++) {
      if (const auto &exprChild = cast<IExpression>(children[exprIndex]); exprChild && containsVariable(exprChild)) {
        stack.emplace(exprChild, -1);
        hasExprChild = true;
        break;
      }

      if (const auto &varChild = cast<Variable>(children[exprIndex])) {
        return varChild;
      }
    }

    if (hasExprChild) {
      continue;
    }

    stack.pop();
  }

  return {};
}

size_t IPolynomExpression::getPositionOfFirstChildWithVariable(const ArgumentPtrVector &children) {
  for (auto i : std::views::iota(0U, children.size())) {
    auto lhsChildExpr = cast<IExpression>(children[i]);

    if (is<Variable>(children[i]) ||
        (lhsChildExpr && containsVariable(lhsChildExpr))) {

      return i;
    }
  }

  return children.size();
}

bool IPolynomExpression::unwrapUnary(ArgumentPtr &lhs) {
  if (const auto lhsExpr = cast<IExpression>(lhs);
      lhsExpr && lhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {

    lhs = lhsExpr->getChildren().front();
    return true;
  }

  return false;
}

}
