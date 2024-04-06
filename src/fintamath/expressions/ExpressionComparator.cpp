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
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath::detail {

using Ordering = std::strong_ordering;

using FunctionPtr = std::shared_ptr<const IFunction>;

using ExpressionPtr = std::shared_ptr<const IExpression>;

using PolynomPtr = std::shared_ptr<const IPolynomExpression>;

using ExpressionTreePathStack = std::stack<std::pair<ExpressionPtr, size_t>>;

struct ChildrenComparatorResult final {
  Ordering postfix = Ordering::equal;
  Ordering prefixFirst = Ordering::equal;
  Ordering prefixLast = Ordering::equal;
  Ordering unary = Ordering::equal;
  Ordering literals = Ordering::equal;
  Ordering size = Ordering::equal;
};

Ordering compareNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options);

Ordering comparePolynoms(const PolynomPtr &lhs, const PolynomPtr &rhs, const ComparatorOptions &options);

Ordering compareExpressions(const ExpressionPtr &lhs, const ExpressionPtr &rhs, const ComparatorOptions &options);

Ordering comparePolynomAndNonPolynom(const PolynomPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options);

Ordering compareExpressionAndNonExpression(const ExpressionPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options);

Ordering compareFunctions(const FunctionPtr &lhs, const FunctionPtr &rhs, const ComparatorOptions &options);

ChildrenComparatorResult compareChildren(const ArgumentPtrVector &lhsChildren, const ArgumentPtrVector &rhsChildren, const ComparatorOptions &options);

bool unwrapUnaryExpression(ArgumentPtr &arg);

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
Ordering compareTerms(const ArgumentPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options) {
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

Ordering compareNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options) {
  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    return options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (*lhs == *rhs) {
    return Ordering::equal;
  }

  if (const auto lhsComp = cast<IComparable>(lhs)) {
    if (const auto rhsComp = cast<IComparable>(rhs)) {
      if (options.comparableOrderInversed) {
        return *lhsComp < *rhsComp ? Ordering::greater : Ordering::less;
      }

      return *lhsComp > *rhsComp ? Ordering::greater : Ordering::less;
    }
  }

  return lhs->toString() < rhs->toString() ? Ordering::greater : Ordering::less;
}

Ordering comparePolynoms(const PolynomPtr &lhs, const PolynomPtr &rhs, const ComparatorOptions &options) {
  const ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), rhs->getChildren(), options);

  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }
  if (childrenComp.size != Ordering::equal) {
    return childrenComp.size;
  }
  if (childrenComp.unary != Ordering::equal) {
    return childrenComp.unary;
  }
  if (childrenComp.prefixFirst != Ordering::equal) {
    return childrenComp.prefixFirst;
  }

  return compareFunctions(lhs->getFunction(), rhs->getFunction(), options);
}

Ordering compareExpressions(const ExpressionPtr &lhs, const ExpressionPtr &rhs, const ComparatorOptions &options) {
  const auto lhsOper = cast<IOperator>(lhs->getFunction());
  const auto rhsOper = cast<IOperator>(rhs->getFunction());

  if ((lhsOper != nullptr) != (rhsOper != nullptr)) {
    return compareFunctions(lhs->getFunction(), rhs->getFunction(), options);
  }

  ComparatorOptions childCompOptions = options;
  childCompOptions.termOrderInversed = false;
  const ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), rhs->getChildren(), childCompOptions);

  if (childrenComp.literals != Ordering::equal) {
    return childrenComp.literals;
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

Ordering comparePolynomAndNonPolynom(const PolynomPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options) {
  const ChildrenComparatorResult childrenComp = compareChildren(lhs->getChildren(), {rhs}, options);

  if (childrenComp.postfix != Ordering::equal) {
    return childrenComp.postfix;
  }

  return childrenComp.prefixFirst;
}

Ordering compareExpressionAndNonExpression(const ExpressionPtr &lhs, const ArgumentPtr &rhs, const ComparatorOptions &options) {
  if (!is<ILiteral>(rhs)) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (const auto res = compareTerms<Variable>(lhs, rhs, options); res != Ordering::equal) {
    return res;
  }

  if (!is<IOperator>(lhs->getFunction())) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (const auto res = compareTerms<ILiteral>(lhs, rhs, options); res != Ordering::equal) {
    return res;
  }

  if (is<Not>(lhs->getFunction())) {
    if (const Ordering res = compare(lhs->getChildren().front(), rhs); res != Ordering::equal) {
      return res;
    }

    return Ordering::less;
  }

  if (is<Mul>(lhs->getFunction()) || is<Pow>(lhs->getFunction())) {
    const ArgumentPtr rhsExpr = makeExpr(*lhs->getFunction(), rhs, Integer(1).clone());
    const Ordering res = compare(lhs, rhsExpr);
    return !options.termOrderInversed ? res : reverse(res);
  }

  return !options.termOrderInversed ? Ordering::greater : Ordering::less;
}

Ordering compareFunctions(const FunctionPtr &lhs, const FunctionPtr &rhs, const ComparatorOptions &options) {
  if (is<IOperator>(lhs) && !is<IOperator>(rhs)) {
    return options.termOrderInversed ? Ordering::greater : Ordering::less;
  }
  if (!is<IOperator>(lhs) && is<IOperator>(rhs)) {
    return !options.termOrderInversed ? Ordering::greater : Ordering::less;
  }

  if (*lhs == *rhs) {
    return Ordering::equal;
  }

  if (lhs->getClass() != rhs->getClass()) {
    return lhs->getClass() < rhs->getClass() ? Ordering::greater : Ordering::less;
  }

  return lhs->toString() < rhs->toString() ? Ordering::greater : Ordering::less;
}

ChildrenComparatorResult compareChildren(const ArgumentPtrVector &lhsChildren, const ArgumentPtrVector &rhsChildren, const ComparatorOptions &options) {
  ChildrenComparatorResult result = {};

  if (lhsChildren.size() != rhsChildren.size()) {
    result.size = lhsChildren.size() > rhsChildren.size() ? Ordering::greater : Ordering::less;
  }

  const size_t lhsPostfixStart = getPositionOfFirstChildWithTerm<Variable>(lhsChildren);
  const size_t rhsPostfixStart = getPositionOfFirstChildWithTerm<Variable>(rhsChildren);
  const size_t prefixSize = std::min(std::max(lhsPostfixStart, rhsPostfixStart),
                                     std::min(lhsChildren.size(), rhsChildren.size()));

  for (const auto i : stdv::iota(0U, prefixSize)) {
    const Ordering childrenComp = compare(lhsChildren[i], rhsChildren[i], options);

    if (childrenComp != Ordering::equal) {
      result.prefixLast = childrenComp;
    }

    if (result.prefixFirst == Ordering::equal) {
      result.prefixFirst = childrenComp;
    }

    if (result.literals == Ordering::equal) {
      result.literals = compareTerms<ILiteral>(lhsChildren[i], rhsChildren[i], {});
    }

    if (result.literals != Ordering::equal && result.prefixLast != Ordering::equal) {
      break;
    }
  }

  for (size_t i = lhsPostfixStart, j = rhsPostfixStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    ArgumentPtr compLhs = lhsChildren[i];
    ArgumentPtr compRhs = rhsChildren[j];

    const bool isLhsUnary = unwrapUnaryExpression(compLhs);
    const bool isRhsUnary = unwrapUnaryExpression(compRhs);

    if (isLhsUnary && isRhsUnary) {
      compLhs = lhsChildren[i];
      compRhs = rhsChildren[j];
    }

    if (result.literals == Ordering::equal) {
      result.literals = compareTerms<ILiteral>(compLhs, compRhs, options);
    }

    if (result.unary == Ordering::equal && isLhsUnary != isRhsUnary) {
      result.unary = !isLhsUnary ? Ordering::greater : Ordering::less;
    }

    if (result.postfix == Ordering::equal) {
      result.postfix = compare(compLhs, compRhs, options);
    }

    if (result.postfix != Ordering::equal) {
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

bool unwrapUnaryExpression(ArgumentPtr &arg) {
  if (const auto expr = cast<IExpression>(arg);
      expr &&
      expr->getFunction()->getArgumentClasses().size() == 1) {

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

Ordering reverse(const Ordering ordering) {
  return 0 <=> ordering;
}

}