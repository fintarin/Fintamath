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
  Ordering prefixLiterals = Ordering::equal;
  Ordering size = Ordering::equal;
};

Ordering compareNonExpressions(const ArgumentPtr &lhs,
                               const ArgumentPtr &rhs,
                               const ComparatorOptions &options);

Ordering comparePolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                         const std::shared_ptr<const IPolynomExpression> &rhs,
                         const ComparatorOptions &options);

Ordering compareExpressions(const std::shared_ptr<const IExpression> &lhs,
                            const std::shared_ptr<const IExpression> &rhs,
                            const ComparatorOptions &options);

Ordering comparePolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                     const ArgumentPtr &rhs,
                                     const ComparatorOptions &options);

Ordering compareExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                           const ArgumentPtr &rhs,
                                           const ComparatorOptions &options);

Ordering compareFunctions(const std::shared_ptr<const IFunction> &lhs,
                          const std::shared_ptr<const IFunction> &rhs,
                          const ComparatorOptions &options);

ChildrenComparatorResult compareChildren(const ArgumentPtrVector &lhsChildren,
                                         const ArgumentPtrVector &rhsChildren,
                                         const ComparatorOptions &options);

bool unwrapUnaryExpression(ArgumentPtr &arg);

bool unwrapEmptyExpression(ArgumentPtr &arg);

Ordering reverse(Ordering ordering);

template <typename T>
size_t getPositionOfFirstChildWithTerm(const ArgumentPtrVector &children) {
  for (auto i : std::views::iota(0U, children.size())) {
    bool containsTerm = containsIf(children[i], [](const ArgumentPtr &child) {
      return is<T>(child);
    });

    if (containsTerm) {
      return i;
    }
  }

  return children.size();
}

template <typename T>
std::shared_ptr<const T> popNextTerm(ExpressionTreePathStack &stack) {
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

      if (const auto &varChild = cast<T>(children[exprIndex])) {
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

template <typename T>
Ordering compareTerms(const ArgumentPtr &lhs,
                      const ArgumentPtr &rhs,
                      const ComparatorOptions &options) {

  ExpressionTreePathStack lhsPath;
  ExpressionTreePathStack rhsPath;

  std::shared_ptr<const T> lhsTerm;
  std::shared_ptr<const T> rhsTerm;

  if (const auto &expr = cast<IExpression>(lhs)) {
    lhsPath.emplace(expr, -1);
    lhsTerm = popNextTerm<T>(lhsPath);
  }
  else if (const auto &term = cast<T>(lhs)) {
    lhsTerm = term;
  }

  if (const auto &expr = cast<IExpression>(rhs)) {
    rhsPath.emplace(expr, -1);
    rhsTerm = popNextTerm<T>(rhsPath);
  }
  else if (const auto &term = cast<T>(rhs)) {
    rhsTerm = term;
  }

  if (lhsTerm && !rhsTerm) {
    return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (!lhsTerm && rhsTerm) {
    return options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  while (lhsTerm && rhsTerm) {
    if (Ordering res = compareNonExpressions(lhsTerm, rhsTerm, options); res != Ordering::equal) {
      return res;
    }

    lhsTerm = popNextTerm<T>(lhsPath);
    rhsTerm = popNextTerm<T>(rhsPath);
  }

  return Ordering::equal;
}

Ordering compare(ArgumentPtr lhs,
                 ArgumentPtr rhs,
                 ComparatorOptions options) {

  unwrapEmptyExpression(lhs);
  unwrapEmptyExpression(rhs);

  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr && !rhsExpr) {
    return compareNonExpressions(lhs, rhs, options);
  }

  auto lhsPolynom = cast<IPolynomExpression>(lhsExpr);
  auto rhsPolynom = cast<IPolynomExpression>(rhsExpr);

  if (lhsPolynom && rhsPolynom) {
    return comparePolynoms(lhsPolynom, rhsPolynom, options);
  }

  if (lhsExpr && !rhsExpr) {
    return compareExpressionAndNonExpression(lhsExpr, rhs, options);
  }

  if (!lhsExpr && rhsExpr) {
    return reverse(compareExpressionAndNonExpression(rhsExpr, lhs, options));
  }

  if (lhsPolynom && !rhsPolynom) {
    return comparePolynomAndNonPolynom(lhsPolynom, rhs, options);
  }

  if (!lhsPolynom && rhsPolynom) {
    return reverse(comparePolynomAndNonPolynom(rhsPolynom, lhs, options));
  }

  return compareExpressions(lhsExpr, rhsExpr, options);
}

Ordering compareNonExpressions(const ArgumentPtr &lhs,
                               const ArgumentPtr &rhs,
                               const ComparatorOptions &options) {

  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    return options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (*lhs == *rhs) {
    return Ordering::equal;
  }

  if (auto lhsComp = cast<IComparable>(lhs)) {
    if (auto rhsComp = cast<IComparable>(rhs)) {
      if (options.comparableOrderInversed) {
        return *lhsComp < *rhsComp ? Ordering::greater : Ordering::less;
      }

      return *lhsComp > *rhsComp ? Ordering::greater : Ordering::less;
    }
  }

  return lhs->toString() < rhs->toString() ? Ordering::greater : Ordering::less;
}

Ordering comparePolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                         const std::shared_ptr<const IPolynomExpression> &rhs,
                         const ComparatorOptions &options) {

  ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), rhs->getChildren(), options);

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

  return compareFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

Ordering compareExpressions(const std::shared_ptr<const IExpression> &lhs,
                            const std::shared_ptr<const IExpression> &rhs,
                            const ComparatorOptions &options) {

  auto lhsOper = cast<IOperator>(lhs->getFunction());
  auto rhsOper = cast<IOperator>(rhs->getFunction());

  if ((lhsOper != nullptr) != (rhsOper != nullptr)) {
    return compareFunctions(lhs->getFunction(), rhs->getFunction(), options);
  }

  ComparatorOptions childCompOptions = options;
  childCompOptions.constantOrderInversed = false;
  ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), rhs->getChildren(), childCompOptions);

  if (childrenComp.prefixVariables != Ordering::equal) {
    return childrenComp.prefixVariables;
  }
  if (childrenComp.prefixLiterals != Ordering::equal) {
    return childrenComp.prefixLiterals;
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

  return compareFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

Ordering comparePolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                     const ArgumentPtr &rhs,
                                     const ComparatorOptions &options) {

  ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), {rhs}, options);

  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }

  return childrenComp.prefixFirst;
}

Ordering compareExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                           const ArgumentPtr &rhs,
                                           const ComparatorOptions &options) {

  if (!is<ILiteral>(rhs)) {
    return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (auto res = compareTerms<Variable>(lhs, rhs, options); res != Ordering::equal) {
    return res;
  }

  if (!is<IOperator>(lhs->getFunction())) {
    return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (auto res = compareTerms<ILiteral>(lhs, rhs, options); res != Ordering::equal) {
    return res;
  }

  if (auto lhsOper = cast<IOperator>(lhs->getFunction())) {
    auto lhsOperPriority = lhsOper->getOperatorPriority();

    switch (lhsOperPriority) {
      case IOperator::Priority::PostfixUnary:
      case IOperator::Priority::PrefixUnary: {
        if (Ordering res = compare(lhs->getChildren().front(), rhs); res != Ordering::equal) {
          return res;
        }

        return Ordering::less;
      }
      case IOperator::Priority::Exponentiation:
      case IOperator::Priority::Multiplication: {
        ArgumentPtr rhsExpr = makeExpr(*lhsOper, rhs, Integer(1).clone());
        Ordering res = compare(lhs, rhsExpr);
        return options.constantOrderInversed ? reverse(res) : res;
      }
      default: {
        break;
      }
    }
  }

  return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
}

Ordering compareFunctions(const std::shared_ptr<const IFunction> &lhs,
                          const std::shared_ptr<const IFunction> &rhs,
                          const ComparatorOptions &options) {

  if (is<IOperator>(lhs) && !is<IOperator>(rhs)) {
    return options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }
  if (!is<IOperator>(lhs) && is<IOperator>(rhs)) {
    return !options.constantOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (*lhs == *rhs) {
    return Ordering::equal;
  }

  if (lhs->getFunctionOrder() != rhs->getFunctionOrder()) {
    return lhs->getFunctionOrder() < rhs->getFunctionOrder() ? Ordering::greater : Ordering::less;
  }

  return lhs->toString() < rhs->toString() ? Ordering::greater : Ordering::less;
}

ChildrenComparatorResult compareChildren(const ArgumentPtrVector &lhsChildren,
                                         const ArgumentPtrVector &rhsChildren,
                                         const ComparatorOptions &options) {

  ChildrenComparatorResult result = {};

  size_t lhsStart = getPositionOfFirstChildWithTerm<Variable>(lhsChildren);
  size_t rhsStart = getPositionOfFirstChildWithTerm<Variable>(rhsChildren);

  for (size_t i = lhsStart, j = rhsStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    ArgumentPtr compLhs = lhsChildren[i];
    ArgumentPtr compRhs = rhsChildren[j];

    bool isLhsUnary = unwrapUnaryExpression(compLhs);
    bool isRhsUnary = unwrapUnaryExpression(compRhs);

    if (isLhsUnary && isRhsUnary) {
      compLhs = lhsChildren[i];
      compRhs = rhsChildren[j];
    }

    if (result.postfixUnary == Ordering::equal && isLhsUnary != isRhsUnary) {
      result.postfixUnary = !isLhsUnary ? Ordering::greater : Ordering::less;
    }

    if (result.postfix == Ordering::equal) {
      result.postfix = compare(compLhs, compRhs, options);
    }

    if (result.postfix != Ordering::equal) {
      break;
    }
  }

  if (result.postfix == Ordering::equal) {
    size_t lhsPostfixSize = lhsChildren.size() - lhsStart;
    size_t rhsPostfixSize = rhsChildren.size() - rhsStart;

    if (lhsPostfixSize != rhsPostfixSize) {
      result.postfix = lhsPostfixSize > rhsPostfixSize ? Ordering::greater : Ordering::less;
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.postfixUnary = Ordering::equal;
  }

  for (auto end = std::min(std::max(lhsStart, rhsStart), std::min(lhsChildren.size(), rhsChildren.size()));
       auto i : std::views::iota(0U, end)) {

    Ordering childrenComp = compare(lhsChildren[i], rhsChildren[i], options);

    if (childrenComp != Ordering::equal) {
      result.prefixLast = childrenComp;
    }

    if (result.prefixFirst == Ordering::equal) {
      result.prefixFirst = childrenComp;
    }

    if (result.prefixVariables == Ordering::equal) {
      result.prefixVariables = compareTerms<Variable>(lhsChildren[i], rhsChildren[i], {});
    }

    if (result.prefixLiterals == Ordering::equal) {
      result.prefixLiterals = compareTerms<ILiteral>(lhsChildren[i], rhsChildren[i], {});
    }

    if (result.prefixLiterals != Ordering::equal && result.prefixLast != Ordering::equal) {
      break;
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.size = lhsChildren.size() > rhsChildren.size() ? Ordering::greater : Ordering::less;
  }

  return result;
}

bool unwrapUnaryExpression(ArgumentPtr &arg) {
  if (const auto expr = cast<IExpression>(arg);
      expr &&
      expr->getFunction()->getFunctionType() == IFunction::Type::Unary) {

    arg = expr->getChildren().front();
    return true;
  }

  return false;
}

bool unwrapEmptyExpression(ArgumentPtr &arg) {
  if (const auto expr = cast<IExpression>(arg);
      expr &&
      !expr->getFunction()) {

    arg = expr->getChildren().front();
    return true;
  }

  return false;
}

Ordering reverse(Ordering ordering) {
  return 0 <=> ordering;
}

}
