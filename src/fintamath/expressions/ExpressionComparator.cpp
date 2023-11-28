#include "fintamath/expressions/ExpressionComparator.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

struct ChildrenComparatorResult {
  int postfix = 0;
  int postfixUnary = 0;
  int prefixFirst = 0;
  int prefixLast = 0;
  int prefixVariables = 0;
  int size = 0;
};

using ExpressionTreePathStack = std::stack<std::pair<const std::shared_ptr<const IExpression>, size_t>>;

int comparatorNonExpressions(const ArgumentPtr &lhs,
                             const ArgumentPtr &rhs,
                             const ComparatorOptions &options);

int comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                       const std::shared_ptr<const IPolynomExpression> &rhs,
                       const ComparatorOptions &options);

int comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                   const ArgumentPtr &rhs,
                                   const ComparatorOptions &options);

int comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                         const ArgumentPtr &rhs,
                                         const ComparatorOptions &options);

int comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                          const std::shared_ptr<const IExpression> &rhs,
                          const ComparatorOptions &options);

int comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                        const std::shared_ptr<const IFunction> &rhs,
                        const ComparatorOptions &options);

int comparatorVariables(const ArgumentPtr &lhs,
                        const ArgumentPtr &rhs,
                        const ComparatorOptions &options);

ChildrenComparatorResult comparatorChildren(const ArgumentPtrVector &lhsChildren,
                                            const ArgumentPtrVector &rhsChildren,
                                            const ComparatorOptions &options);

std::shared_ptr<const Variable> popNextVariable(ExpressionTreePathStack &stack);

size_t getPositionOfFirstChildWithVariable(const ArgumentPtrVector &children);

bool unwrapUnary(ArgumentPtr &lhs);

int comparator(const ArgumentPtr &lhs,
               const ArgumentPtr &rhs,
               ComparatorOptions options) {

  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr && !rhsExpr) {
    return comparatorNonExpressions(lhs, rhs, options);
  }

  auto lhsPolynom = cast<IPolynomExpression>(lhsExpr);
  auto rhsPolynom = cast<IPolynomExpression>(rhsExpr);

  if (lhsPolynom && rhsPolynom) {
    return comparatorPolynoms(lhsPolynom, rhsPolynom, options);
  }

  if (lhsExpr && !rhsExpr) {
    return comparatorExpressionAndNonExpression(lhsExpr, rhs, options);
  }

  if (!lhsExpr && rhsExpr) {
    return comparatorExpressionAndNonExpression(rhsExpr, lhs, options) * -1;
  }

  if (lhsPolynom && !rhsPolynom) {
    return comparatorPolynomAndNonPolynom(lhsPolynom, rhs, options);
  }

  if (!lhsPolynom && rhsPolynom) {
    return comparatorPolynomAndNonPolynom(rhsPolynom, lhs, options) * -1;
  }

  return comparatorExpressions(lhsExpr, rhsExpr, options);
}

int comparatorNonExpressions(const ArgumentPtr &lhs,
                             const ArgumentPtr &rhs,
                             const ComparatorOptions &options) {

  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !options.termsOrderInversed ? -1 : 1;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return options.termsOrderInversed ? -1 : 1;
  }

  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !options.termsOrderInversed ? -1 : 1;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    return options.termsOrderInversed ? -1 : 1;
  }

  if (*lhs == *rhs) {
    return 0;
  }

  if (auto lhsComp = cast<IComparable>(lhs)) {
    if (auto rhsComp = cast<IComparable>(rhs)) {
      if (options.comparableOrderInversed) {
        return *lhsComp < *rhsComp ? -1 : 1;
      }

      return *lhsComp > *rhsComp ? -1 : 1;
    }
  }

  return lhs->toString() < rhs->toString() ? -1 : 1;
}

int comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                       const std::shared_ptr<const IPolynomExpression> &rhs,
                       const ComparatorOptions &options) {

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), rhs->getChildren(), options);

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

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

int comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                   const ArgumentPtr &rhs,
                                   const ComparatorOptions &options) {

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), {rhs}, options);
  int res = -1;

  if (childrenComp.postfix != 0) {
    res = childrenComp.postfix;
  }
  else if (childrenComp.prefixFirst != 0) {
    res = childrenComp.prefixFirst;
  }

  return res * (options.termsOrderInversed ? -1 : 1);
}

int comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                         const ArgumentPtr &rhs,
                                         const ComparatorOptions &options) {

  if (!is<Variable>(rhs)) {
    return !options.termsOrderInversed ? -1 : 1;
  }

  if (auto res = comparatorVariables(lhs, rhs, options); res != 0) {
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
        return comparator(lhs, rhsExpr) * (options.termsOrderInversed ? -1 : 1);
      }
      default: {
        break;
      }
    }
  }

  return !options.termsOrderInversed ? -1 : 1;
}

int comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                          const std::shared_ptr<const IExpression> &rhs,
                          const ComparatorOptions &options) {

  auto lhsOper = cast<IOperator>(lhs->getFunction());
  auto rhsOper = cast<IOperator>(rhs->getFunction());

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), rhs->getChildren(), options);

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

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

int comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                        const std::shared_ptr<const IFunction> &rhs,
                        const ComparatorOptions & /*options*/) {

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

int comparatorVariables(const ArgumentPtr &lhs,
                        const ArgumentPtr &rhs,
                        const ComparatorOptions &options) {

  ExpressionTreePathStack lhsPath;
  ExpressionTreePathStack rhsPath;

  std::shared_ptr<const Variable> lhsVar;
  std::shared_ptr<const Variable> rhsVar;

  if (const auto &expr = cast<IExpression>(lhs)) {
    lhsPath.emplace(expr, -1);
    lhsVar = popNextVariable(lhsPath);
  }
  else if (const auto &var = cast<Variable>(lhs)) {
    lhsVar = var;
  }

  if (const auto &expr = cast<IExpression>(rhs)) {
    rhsPath.emplace(expr, -1);
    rhsVar = popNextVariable(rhsPath);
  }
  else if (const auto &var = cast<Variable>(rhs)) {
    rhsVar = var;
  }

  if (lhsVar && !rhsVar) {
    return !options.termsOrderInversed ? -1 : 1;
  }

  if (!lhsVar && rhsVar) {
    return options.termsOrderInversed ? -1 : 1;
  }

  while (lhsVar && rhsVar) {
    if (int res = comparatorNonExpressions(lhsVar, rhsVar, options); res != 0) {
      return res;
    }

    lhsVar = popNextVariable(lhsPath);
    rhsVar = popNextVariable(rhsPath);
  }

  return 0;
}

ChildrenComparatorResult comparatorChildren(const ArgumentPtrVector &lhsChildren,
                                            const ArgumentPtrVector &rhsChildren,
                                            const ComparatorOptions &options) {

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
      result.postfix = comparator(compLhs, compRhs, options);
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

    int childrenComp = comparator(lhsChildren[i], rhsChildren[i], options);

    if (childrenComp != 0) {
      result.prefixLast = childrenComp;
    }

    if (result.prefixFirst == 0) {
      result.prefixFirst = childrenComp;
    }

    if (result.prefixVariables == 0) {
      result.prefixVariables = comparatorVariables(lhsChildren[i], rhsChildren[i], {});
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

std::shared_ptr<const Variable> popNextVariable(ExpressionTreePathStack &stack) {
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

size_t getPositionOfFirstChildWithVariable(const ArgumentPtrVector &children) {
  for (auto i : std::views::iota(0U, children.size())) {
    auto lhsChildExpr = cast<IExpression>(children[i]);

    if (is<Variable>(children[i]) ||
        (lhsChildExpr && containsVariable(lhsChildExpr))) {

      return i;
    }
  }

  return children.size();
}

bool unwrapUnary(ArgumentPtr &lhs) {
  if (const auto lhsExpr = cast<IExpression>(lhs);
      lhsExpr && lhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {

    lhs = lhsExpr->getChildren().front();
    return true;
  }

  return false;
}

}
