#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include <algorithm>
#include <cctype>
#include <compare>
#include <cstddef>
#include <list>
#include <memory>
#include <ranges>
#include <string>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionComparator.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
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

ArgumentPtr IPolynomExpression::preSimplify(const bool isTranformOverriden) const {
  if (getState() >= State::PreSimplify) {
    return {};
  }

  ArgumentPtrVector newChildren = children;
  compress(newChildren);
  sort(newChildren);

  auto newExpr = cast<IPolynomExpression>(makeExpr(*getFunction(), newChildren));
  return newExpr->IExpression::preSimplify(isTranformOverriden);
}

ArgumentPtr IPolynomExpression::tranform(const State newState) const {
  std::list<ArgumentPtr> newChildren(children.begin(), children.end());

  auto rhsIter = newChildren.begin();
  rhsIter++;

  for (; rhsIter != newChildren.end(); ++rhsIter) {
    auto lhsIter = rhsIter;
    lhsIter--;

    const ArgumentPtr &lhs = *lhsIter;
    const ArgumentPtr &rhs = *rhsIter;

    ArgumentPtr res = cast<IPolynomExpression>(makeExpr(*func, lhs, rhs))->callFunction();

    if (!res) {
      switch (newState) {
        case State::PreSimplify: {
          res = useSimplifyFunctions(getFunctionsForPreSimplify(), *func, lhs, rhs);
          break;
        }
        case State::Simplify: {
          res = useSimplifyFunctions(getFunctionsForPostSimplify(), *func, lhs, rhs);
          break;
        }
        default: {
          break;
        }
      }
    }

    if (res) {
      newChildren.erase(rhsIter);
      *lhsIter = res;
      rhsIter = lhsIter;
    }
  }

  if (newChildren.size() == 1) {
    return newChildren.front();
  }

  if (newChildren.size() != children.size()) {
    ArgumentPtrVector newChildrenVect(newChildren.begin(), newChildren.end());
    return makeExpr(*func, newChildrenVect);
  }

  return IExpression::tranform(newState);
}

void IPolynomExpression::compress(ArgumentPtrVector &newChildren) const {
  size_t i = 0;

  while (i < newChildren.size()) {
    auto &child = newChildren[i];

    if (const auto childPolynom = cast<IPolynomExpression>(child); childPolynom && *childPolynom->func == *func) {
      std::swap(child, newChildren.back());
      newChildren.pop_back();
      newChildren.insert(newChildren.end(),
                         childPolynom->children.begin(),
                         childPolynom->children.end());
    }
    else {
      i++;
    }
  }
}

void IPolynomExpression::sort(ArgumentPtrVector &newChildren) const {
  std::ranges::stable_sort(newChildren, [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return compare(lhs, rhs) == std::strong_ordering::greater;
  });
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

}