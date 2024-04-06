#include "fintamath/expressions/ExpressionComparator.hpp"

#include <algorithm>
#include <compare>
#include <cstddef>
#include <memory>
#include <ranges>
#include <stack>
#include <utility>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"

#include <any>

namespace fintamath::detail {

using Ordering = std::strong_ordering;

using FunctionPtr = std::shared_ptr<const IFunction>;

using ExpressionPtr = std::shared_ptr<const IExpression>;

using PolynomPtr = std::shared_ptr<const IPolynomExpression>;

using ExpressionTreePathStack = std::stack<std::pair<ExpressionPtr, size_t>>;

struct ChildrenComparatorResult final {
  Ordering postfix = Ordering::equal;
  Ordering prefix = Ordering::equal;
  Ordering literals = Ordering::equal;
};

Ordering compareNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs, ComparatorOptions options);

Ordering comparePolynoms(const PolynomPtr &lhs, const PolynomPtr &rhs, ComparatorOptions options);

Ordering compareExpressions(const ExpressionPtr &lhs, const ExpressionPtr &rhs, ComparatorOptions options);

Ordering comparePolynomAndNonPolynom(const PolynomPtr &lhs, const ArgumentPtr &rhs, ComparatorOptions options);

Ordering compareExpressionAndNonExpression(const ExpressionPtr &lhs, const ArgumentPtr &rhs, ComparatorOptions options);

Ordering compareFunctions(const FunctionPtr &lhs, const FunctionPtr &rhs);

ChildrenComparatorResult compareChildren(const ArgumentPtrVector &lhsChildren, const ArgumentPtrVector &rhsChildren, ComparatorOptions options);

bool unwrapEmptyExpression(ArgumentPtr &arg);

Ordering reverse(Ordering ordering);

template <typename Term>
size_t getPositionOfFirstChildWithTerm(const ArgumentPtrVector &children) {
  for (size_t i = 0; i < children.size(); i++) {
    if (containsIf(children[i], [](const ArgumentPtr &child) { return is<Term>(child); })) {
      return i;
    }
  }

  return children.size();
}

template <typename Term>
std::shared_ptr<const Term> popNextTerm(ExpressionTreePathStack &stack) {
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

      if (const auto &varChild = cast<Term>(children[exprIndex])) {
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

template <typename Term>
Ordering compareTerms(const ArgumentPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions options) {
  ExpressionTreePathStack lhsPath;
  ExpressionTreePathStack rhsPath;

  std::shared_ptr<const Term> lhsTerm;
  std::shared_ptr<const Term> rhsTerm;

  if (const auto &expr = cast<IExpression>(lhs)) {
    lhsPath.emplace(expr, -1);
    lhsTerm = popNextTerm<Term>(lhsPath);
  }
  else if (const auto &term = cast<Term>(lhs)) {
    lhsTerm = term;
  }

  if (const auto &expr = cast<IExpression>(rhs)) {
    rhsPath.emplace(expr, -1);
    rhsTerm = popNextTerm<Term>(rhsPath);
  }
  else if (const auto &term = cast<Term>(rhs)) {
    rhsTerm = term;
  }

  if (lhsTerm && !rhsTerm) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (!lhsTerm && rhsTerm) {
    return options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  while (lhsTerm && rhsTerm) {
    if (const Ordering res = compareNonExpressions(lhsTerm, rhsTerm, options); res != Ordering::equal) {
      return res;
    }

    lhsTerm = popNextTerm<Term>(lhsPath);
    rhsTerm = popNextTerm<Term>(rhsPath);
  }

  return Ordering::equal;
}

Ordering compare(ArgumentPtr lhs, ArgumentPtr rhs, const ComparatorOptions options) {
  unwrapEmptyExpression(lhs);
  unwrapEmptyExpression(rhs);

  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr && !rhsExpr) {
    return compareNonExpressions(lhs, rhs, options);
  }

  const auto lhsPolynom = cast<IPolynomExpression>(lhsExpr);
  const auto rhsPolynom = cast<IPolynomExpression>(rhsExpr);

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

Ordering compareNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions options) {
  Ordering ordering = Ordering::equal;

  if (!lhs && !rhs) {
    return ordering;
  }

  if (lhs && !rhs) {
    ordering = Ordering::greater;
  }
  else if (!lhs && rhs) {
    ordering = Ordering::less;
  }
  else if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    ordering = Ordering::greater;
  }
  else if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    ordering = Ordering::less;
  }
  else if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    ordering = Ordering::greater;
  }
  else if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    ordering = Ordering::less;
  }

  if (ordering != Ordering::equal || *lhs == *rhs) {
    return options.termOrderInversed ? reverse(ordering) : ordering;
  }

  const auto lhsComp = cast<IComparable>(lhs);
  const auto rhsComp = cast<IComparable>(rhs);

  if (lhsComp && rhsComp) {
    ordering = *lhsComp <=> *rhsComp;

    if (options.comparableOrderInversed) {
      ordering = reverse(ordering);
    }
  }
  else {
    ordering = rhs->toString() <=> lhs->toString();
  }

  return ordering;
}

Ordering comparePolynoms(const PolynomPtr &lhs, const PolynomPtr &rhs, const ComparatorOptions options) {
  if (*lhs->getFunction() != *rhs->getFunction()) {
    return compareFunctions(lhs->getFunction(), rhs->getFunction());
  }

  const ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), rhs->getChildren(), options);

  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }
  if (childrenComp.prefix != Ordering::equal) {
    return childrenComp.prefix;
  }

  return Ordering::equal;
}

Ordering compareExpressions(const ExpressionPtr &lhs, const ExpressionPtr &rhs, const ComparatorOptions options) {
  if (*lhs->getFunction() != *rhs->getFunction()) {
    return compareFunctions(lhs->getFunction(), rhs->getFunction());
  }

  ArgumentPtrVector lhsChildren = lhs->getChildren();
  ArgumentPtrVector rhsChildren = rhs->getChildren();

  if (is<Pow>(lhs->getFunction()) && is<Pow>(rhs->getFunction())) {
    std::ranges::reverse(lhsChildren);
    std::ranges::reverse(rhsChildren);
  }

  ComparatorOptions childCompOptions = options;
  childCompOptions.termOrderInversed = false;
  const ChildrenComparatorResult childrenComp = compareChildren(lhsChildren, rhsChildren, childCompOptions);

  if (childrenComp.literals != Ordering::equal) {
    return childrenComp.literals;
  }
  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }
  if (childrenComp.prefix != Ordering::equal) {
    return childrenComp.prefix;
  }

  return Ordering::equal;
}

Ordering comparePolynomAndNonPolynom(const PolynomPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions options) {
  const ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), {rhs}, options);

  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }

  return childrenComp.prefix;
}

Ordering compareExpressionAndNonExpression(const ExpressionPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions options) {
  if (!is<ILiteral>(rhs)) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (const auto res = compareTerms<Variable>(lhs, rhs, options); res != Ordering::equal) {
    return res;
  }

  if ((is<Mul>(lhs->getFunction()) || is<Pow>(lhs->getFunction())) &&
      !is<IExpression>(lhs->getChildren().front())) {

    const ArgumentPtr rhsExpr = makeExpr(*lhs->getFunction(), rhs, Integer(1).clone());
    return compare(lhs, rhsExpr, options);
  }

  return !options.termOrderInversed ? Ordering::greater : Ordering::less;
}

Ordering compareFunctions(const FunctionPtr &lhs, const FunctionPtr &rhs) {
  if (lhs->getClass() != rhs->getClass()) {
    return rhs->getClass() <=> lhs->getClass();
  }

  return rhs->toString() <=> lhs->toString();
}

ChildrenComparatorResult compareChildren(const ArgumentPtrVector &lhsChildren, const ArgumentPtrVector &rhsChildren, const ComparatorOptions options) {
  ChildrenComparatorResult result = {};

  const size_t lhsPostfixStart = getPositionOfFirstChildWithTerm<Variable>(lhsChildren);
  const size_t rhsPostfixStart = getPositionOfFirstChildWithTerm<Variable>(rhsChildren);
  const size_t prefixSize = std::min(std::max(lhsPostfixStart, rhsPostfixStart),
                                     std::min(lhsChildren.size(), rhsChildren.size()));

  for (size_t i = 0; i < prefixSize; i++) {
    if (result.prefix == Ordering::equal) {
      result.prefix = compare(lhsChildren[i], rhsChildren[i], options);
    }

    if (result.literals == Ordering::equal) {
      result.literals = compareTerms<ILiteral>(lhsChildren[i], rhsChildren[i], {});
    }

    if (result.prefix != Ordering::equal && result.literals != Ordering::equal) {
      break;
    }
  }

  for (size_t i = lhsPostfixStart, j = rhsPostfixStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    if (result.postfix == Ordering::equal) {
      result.postfix = compare(lhsChildren[i], rhsChildren[j], options);
    }

    if (result.literals == Ordering::equal) {
      result.literals = compareTerms<ILiteral>(lhsChildren[i], rhsChildren[j], options);
    }

    if (result.postfix != Ordering::equal && result.literals != Ordering::equal) {
      break;
    }
  }

  if (result.postfix == Ordering::equal) {
    const size_t lhsPostfixSize = lhsChildren.size() - lhsPostfixStart;
    const size_t rhsPostfixSize = rhsChildren.size() - rhsPostfixStart;

    if (lhsPostfixSize != rhsPostfixSize) {
      result.postfix = lhsPostfixSize > rhsPostfixSize ? Ordering::greater : Ordering::less;
    }
  }

  return result;
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

Ordering reverse(const Ordering ordering) {
  return 0 <=> ordering;
}

}