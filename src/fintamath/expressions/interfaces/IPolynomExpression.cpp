#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include <algorithm>
#include <cctype>
#include <compare>
#include <cstddef>
#include <memory>
#include <ranges>
#include <string>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionComparator.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/binary/CompExpr.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/MulOper.hpp"

namespace fintamath {

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IPolynomExpression)

using namespace detail;

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

void IPolynomExpression::setChildren(const ArgumentPtrVector &childVect) {
  (void)makeExpr(*func, childVect);

  children = childVect;
}

std::string IPolynomExpression::toString() const {
  const auto &outFunc = getOutputFunction();
  const auto outOper = cast<IOperator>(outFunc);

  if (!outOper) {
    return functionToString(*outFunc, children);
  }

  std::string result = childToString(*outOper, children.front(), {});

  for (size_t i = 1; i < children.size(); i++) {
    const std::string childStr = childToString(*outOper, children[i], children[i - 1]);

    if (childStr.size() > 2 && childStr[0] == ' ' && std::isdigit(childStr[1]) && std::isdigit(result.back())) {
      result += MulOper{}.toString() + childStr.substr(1);
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

void IPolynomExpression::simplifyRec(const bool isPostSimplify) {
  compress();
  sort();

  bool isExprSimplified = true;

  // TODO: refactor this loop
  for (size_t i = 1; i < children.size(); i++) {
    const ArgumentPtr &lhs = children[i - 1];
    const ArgumentPtr &rhs = children[i];

    if (auto res = simplifyUndefined(*func, lhs, rhs)) {
      children = {res};
      break;
    }

    ArgumentPtr res = callFunction(*func, {lhs, rhs});
    const bool isResSimplified = res != nullptr;

    if (!res) {
      res = isPostSimplify ? useSimplifyFunctions(getFunctionsForPostSimplify(),
                                                  *func,
                                                  children[i - 1],
                                                  children[i])
                           : useSimplifyFunctions(getFunctionsForPreSimplify(),
                                                  *func,
                                                  children[i - 1],
                                                  children[i]);
    }

    if (!res) {
      continue;
    }

    if (!isResSimplified) {
      const ArgumentPtr prevExpr = makeExpr(*getFunction(), lhs, rhs);

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

    children.erase(children.begin() + static_cast<ptrdiff_t>(i) - 1);
    children.erase(children.begin() + static_cast<ptrdiff_t>(i) - 1);
    children.emplace_back(res);

    i--;
    isExprSimplified = false;
  }

  if (!isExprSimplified) {
    simplifyRec(isPostSimplify);
  }
}

void IPolynomExpression::simplifyChildren(const bool isPostSimplify) {
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
  const std::string childStr = operatorChildToString(oper, inChild);
  const std::string operStr = prevChild ? putInSpaces(oper.toString()) : "";
  return operStr + childStr;
}

bool IPolynomExpression::isTermOrderInversed() const noexcept {
  return false;
}

bool IPolynomExpression::isComparableOrderInversed() const noexcept {
  return false;
}

std::strong_ordering IPolynomExpression::compare(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  const ComparatorOptions options = {
      .termOrderInversed = isTermOrderInversed(),
      .comparableOrderInversed = isComparableOrderInversed(),
  };
  return fintamath::compare(lhs, rhs, options);
}

void IPolynomExpression::sort() {
  std::ranges::stable_sort(children, [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return compare(lhs, rhs) == std::strong_ordering::greater;
  });
}

}