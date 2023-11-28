#include "fintamath/expressions/ExpressionComparator.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

using ExpressionTreePathStack = std::stack<std::pair<const std::shared_ptr<const IExpression>, size_t>>;

using Ordering = std::strong_ordering;

struct ChildrenComparatorResult {
  Ordering postfix = Ordering::equal;
  Ordering postfixUnary = Ordering::equal;
  Ordering prefixFirst = Ordering::equal;
  Ordering prefixLast = Ordering::equal;
  Ordering prefixVariables = Ordering::equal;
  Ordering size = Ordering::equal;
};

Ordering comparatorNonExpressions(const ArgumentPtr &lhs,
                                  const ArgumentPtr &rhs,
                                  const ComparatorOptions &options);

Ordering comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                            const std::shared_ptr<const IPolynomExpression> &rhs,
                            const ComparatorOptions &options);

Ordering comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                        const ArgumentPtr &rhs,
                                        const ComparatorOptions &options);

Ordering comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                              const ArgumentPtr &rhs,
                                              const ComparatorOptions &options);

Ordering comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                               const std::shared_ptr<const IExpression> &rhs,
                               const ComparatorOptions &options);

Ordering comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                             const std::shared_ptr<const IFunction> &rhs,
                             const ComparatorOptions &options);

Ordering comparatorVariables(const ArgumentPtr &lhs,
                             const ArgumentPtr &rhs,
                             const ComparatorOptions &options);

ChildrenComparatorResult comparatorChildren(const ArgumentPtrVector &lhsChildren,
                                            const ArgumentPtrVector &rhsChildren,
                                            const ComparatorOptions &options);

std::shared_ptr<const Variable> popNextVariable(ExpressionTreePathStack &stack);

size_t getPositionOfFirstChildWithVariable(const ArgumentPtrVector &children);

bool unwrapUnary(ArgumentPtr &lhs);

Ordering reverse(Ordering ordering);

Ordering comparator(const ArgumentPtr &lhs,
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
    return reverse(comparatorExpressionAndNonExpression(rhsExpr, lhs, options));
  }

  if (lhsPolynom && !rhsPolynom) {
    return comparatorPolynomAndNonPolynom(lhsPolynom, rhs, options);
  }

  if (!lhsPolynom && rhsPolynom) {
    return reverse(comparatorPolynomAndNonPolynom(rhsPolynom, lhs, options));
  }

  return comparatorExpressions(lhsExpr, rhsExpr, options);
}

Ordering comparatorNonExpressions(const ArgumentPtr &lhs,
                                  const ArgumentPtr &rhs,
                                  const ComparatorOptions &options) {

  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }

  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    return options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }

  if (*lhs == *rhs) {
    return Ordering::equal;
  }

  if (auto lhsComp = cast<IComparable>(lhs)) {
    if (auto rhsComp = cast<IComparable>(rhs)) {
      if (options.comparableOrderInversed) {
        return *lhsComp < *rhsComp ? Ordering::less : Ordering::greater;
      }

      return *lhsComp > *rhsComp ? Ordering::less : Ordering::greater;
    }
  }

  return lhs->toString() < rhs->toString() ? Ordering::less : Ordering::greater;
}

Ordering comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                            const std::shared_ptr<const IPolynomExpression> &rhs,
                            const ComparatorOptions &options) {

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), rhs->getChildren(), options);

  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }
  if (childrenComp.postfixUnary != Ordering::equal) {
    return childrenComp.postfixUnary;
  }
  if (childrenComp.size != Ordering::equal) {
    return childrenComp.size;
  }
  if (childrenComp.prefixFirst != Ordering::equal) {
    return childrenComp.prefixFirst;
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

Ordering comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                        const ArgumentPtr &rhs,
                                        const ComparatorOptions &options) {

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), {rhs}, options);
  Ordering res = Ordering::less;

  if (childrenComp.postfix != Ordering::equal) {
    res = childrenComp.postfix;
  }
  else if (childrenComp.prefixFirst != Ordering::equal) {
    res = childrenComp.prefixFirst;
  }

  return options.termsOrderInversed ? reverse(res) : res;
}

Ordering comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                              const ArgumentPtr &rhs,
                                              const ComparatorOptions &options) {

  if (!is<Variable>(rhs)) {
    return !options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }

  if (auto res = comparatorVariables(lhs, rhs, options); res != Ordering::equal) {
    return res;
  }

  if (auto lhsOper = cast<IOperator>(lhs->getFunction())) {
    auto lhsOperPriority = lhsOper->getOperatorPriority();

    switch (lhsOperPriority) {
      case IOperator::Priority::PostfixUnary:
      case IOperator::Priority::PrefixUnary: {
        if (Ordering res = comparator(lhs->getChildren().front(), rhs); res != Ordering::equal) {
          return res;
        }

        return Ordering::greater;
      }
      case IOperator::Priority::Exponentiation:
      case IOperator::Priority::Multiplication: {
        ArgumentPtr rhsExpr = makeExpr(*lhsOper, rhs, Integer(1).clone());
        Ordering res = comparator(lhs, rhsExpr);
        return options.termsOrderInversed ? reverse(res) : res;
      }
      default: {
        break;
      }
    }
  }

  return !options.termsOrderInversed ? Ordering::less : Ordering::greater;
}

Ordering comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                               const std::shared_ptr<const IExpression> &rhs,
                               const ComparatorOptions &options) {

  auto lhsOper = cast<IOperator>(lhs->getFunction());
  auto rhsOper = cast<IOperator>(rhs->getFunction());

  ChildrenComparatorResult childrenComp = comparatorChildren(lhs->getChildren(), rhs->getChildren(), options);

  if (childrenComp.prefixVariables != Ordering::equal) {
    return childrenComp.prefixVariables;
  }
  if (childrenComp.size != Ordering::equal) {
    return childrenComp.size;
  }
  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }

  if (is<IOperator>(lhs->getFunction()) && is<IOperator>(rhs->getFunction())) {
    if (childrenComp.prefixLast != Ordering::equal) {
      return childrenComp.prefixLast;
    }
  }
  else {
    if (childrenComp.prefixFirst != Ordering::equal) {
      return childrenComp.prefixFirst;
    }
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

Ordering comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                             const std::shared_ptr<const IFunction> &rhs,
                             const ComparatorOptions & /*options*/) {

  if (is<IOperator>(lhs) && !is<IOperator>(rhs)) {
    return Ordering::less;
  }
  if (!is<IOperator>(lhs) && is<IOperator>(rhs)) {
    return Ordering::greater;
  }

  if (*lhs == *rhs) {
    return Ordering::equal;
  }

  return lhs->toString() < rhs->toString() ? Ordering::less : Ordering::greater;
}

Ordering comparatorVariables(const ArgumentPtr &lhs,
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
    return !options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }

  if (!lhsVar && rhsVar) {
    return options.termsOrderInversed ? Ordering::less : Ordering::greater;
  }

  while (lhsVar && rhsVar) {
    if (Ordering res = comparatorNonExpressions(lhsVar, rhsVar, options); res != Ordering::equal) {
      return res;
    }

    lhsVar = popNextVariable(lhsPath);
    rhsVar = popNextVariable(rhsPath);
  }

  return Ordering::equal;
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

    if (result.postfixUnary == Ordering::equal && isLhsUnary != isRhsUnary) {
      result.postfixUnary = !isLhsUnary ? Ordering::less : Ordering::greater;
    }

    if (result.postfix == Ordering::equal) {
      result.postfix = comparator(compLhs, compRhs, options);
    }

    if (result.postfix != Ordering::equal) {
      break;
    }
  }

  if (result.postfix == Ordering::equal) {
    size_t lhsPostfixSize = lhsChildren.size() - lhsStart;
    size_t rhsPostfixSize = rhsChildren.size() - rhsStart;

    if (lhsPostfixSize != rhsPostfixSize) {
      result.postfix = lhsPostfixSize > rhsPostfixSize ? Ordering::less : Ordering::greater;
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.postfixUnary = Ordering::equal;
  }

  for (auto end = std::min(std::max(lhsStart, rhsStart), std::min(lhsChildren.size(), rhsChildren.size()));
       auto i : std::views::iota(0U, end)) {

    Ordering childrenComp = comparator(lhsChildren[i], rhsChildren[i], options);

    if (childrenComp != Ordering::equal) {
      result.prefixLast = childrenComp;
    }

    if (result.prefixFirst == Ordering::equal) {
      result.prefixFirst = childrenComp;
    }

    if (result.prefixVariables == Ordering::equal) {
      result.prefixVariables = comparatorVariables(lhsChildren[i], rhsChildren[i], {});
    }

    if (result.prefixVariables != Ordering::equal && result.prefixLast != Ordering::equal) {
      break;
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.size = lhsChildren.size() > rhsChildren.size() ? Ordering::less : Ordering::greater;
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

Ordering reverse(Ordering ordering) {
  return 0 <=> ordering;
}

}
