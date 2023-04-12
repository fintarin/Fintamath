#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

shared_ptr<IFunction> IPolynomExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IPolynomExpression::getChildren() const {
  return children;
}

string IPolynomExpression::toString() const {
  string result;

  result += childToString(children.front(), true);

  for (size_t i = 1; i < children.size(); i++) {
    result += childToString(children[i]);
  }

  if (result.empty()) {
    return binaryOperatorToString(cast<IOperator>(*func), children);
  }

  return result;
}

string IPolynomExpression::childToString(const ArgumentPtr & /*child*/, bool /*isFirst*/) const {
  return {};
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

ArgumentPtr IPolynomExpression::preSimplify(size_t /*lhsChildNum*/, size_t /*rhsChildNum*/) const {
  return {};
}

ArgumentPtr IPolynomExpression::postSimplify(size_t /*lhsChildNum*/, size_t /*rhsChildNum*/) const {
  return {};
}

void IPolynomExpression::preSimplifyRec() {
  size_t childrenSize = children.size();

  for (int64_t i = 0; i < children.size() - 1; i++) {
    for (int64_t j = i + 1; j < children.size(); j++) {
      if (auto res = preSimplify(i, j)) {
        children[i] = res;
        children.erase(children.begin() + j);
      }
    }
  }

  if (children.size() != childrenSize) {
    preSimplifyRec();
  }
}

void IPolynomExpression::postSimplifyRec() {
  size_t childrenSize = children.size();

  for (int64_t i = 0; i < children.size() - 1; i++) {
    for (int64_t j = i + 1; j < children.size(); j++) {
      if (ArgumentPtr res = callFunction(*func, {children[i], children[j]})) {
        children[i] = res;
        children.erase(children.begin() + j);
      }
      else if (auto res = postSimplify(i, j)) {
        children[i] = res;
        children.erase(children.begin() + j);
      }
    }
  }

  if (children.size() != childrenSize) {
    postSimplifyRec();
  }
}

IPolynomExpression::FunctionsVector IPolynomExpression::getSimplifyFunctions() const {
  return {};
}

void IPolynomExpression::globalSimplifyRec() {
  size_t childrenSize = children.size();
  FunctionsVector functions = getSimplifyFunctions();

  for (const auto &function : functions) {
    for (int64_t i = 0; i < children.size() - 1; i++) {
      for (int64_t j = i + 1; j < children.size(); j++) {
        const ArgumentPtr &lhsChild = children[i];
        const ArgumentPtr &rhsChild = children[j];
        if (auto res = function(lhsChild, rhsChild)) {
          children[i] = res;
          children.erase(children.begin() + j);
        }
      }
      ArgumentsPtrVector oldChildren = children;
      children.clear();

      for (auto &child : oldChildren) {
        addElement(child);
      }
    }
  }

  if (children.size() != childrenSize) {
    globalSimplifyRec();
  }
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

  simpl->postSimplifyRec();
  simpl->globalSimplifyRec();
  simpl->sort();

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

bool IPolynomExpression::isTermsOrderInversed() const {
  return false;
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
    return comparatorTerms(lhs, rhs);
  }

  {
    ArgumentsPtrVector lhsVars;

    if (lhsExpr) {
      lhsVars = lhsExpr->getVariables();
    }
    else if (is<Variable>(lhs)) {
      lhsVars = {lhs};
    }

    ArgumentsPtrVector rhsVars;

    if (rhsExpr) {
      rhsVars = rhsExpr->getVariables();
    }
    else if (is<Variable>(rhs)) {
      rhsVars = {rhs};
    }

    if (int res = comparatorVariables(lhsVars, rhsVars); res != 0) {
      return res;
    }
  }

  {
    ArgumentsPtrVector lhsChildren;

    if (is<IPolynomExpression>(lhsExpr)) {
      lhsChildren = lhsExpr->getChildren();
    }
    else {
      lhsChildren = {lhs};
    }

    ArgumentsPtrVector rhsChildren;

    if (is<IPolynomExpression>(rhsExpr)) {
      rhsChildren = rhsExpr->getChildren();
    }
    else {
      rhsChildren = {rhs};
    }

    if (lhsChildren.size() > 1 || rhsChildren.size() > 1) {
      if (int res = comparatorChildren(lhsChildren, rhsChildren); res != 0) {
        return res;
      }
    }
  }

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

  return comparatorFunctions(lhsExpr, rhsExpr);
}

int IPolynomExpression::comparatorTerms(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
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
      return *lhsComp > *rhsComp ? -1 : 1;
    }
  }

  return lhs->toString() < rhs->toString() ? -1 : 1;
}

int IPolynomExpression::comparatorVariables(const ArgumentsPtrVector &lhsVars,
                                            const ArgumentsPtrVector &rhsVars) const {

  for (size_t i = 0; i < std::min(lhsVars.size(), rhsVars.size()); i++) {
    if (*lhsVars[i] != *rhsVars[i]) {
      return (lhsVars[i]->toString() < rhsVars[i]->toString()) ? -1 : 1;
    }
  }

  if (!lhsVars.empty() && rhsVars.empty()) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (lhsVars.empty() && !rhsVars.empty()) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  return 0;
}

int IPolynomExpression::comparatorChildren(const ArgumentsPtrVector &lhsChildren,
                                           const ArgumentsPtrVector &rhsChildren) const {

  for (size_t i = 0, j = 0; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    for (; i < lhsChildren.size(); i++) {
      if (is<Variable>(lhsChildren[i])) {
        break;
      }
      if (auto lhsChildExpr = cast<IExpression>(lhsChildren[i]);
          lhsChildExpr && !lhsChildExpr->getVariables().empty()) {
        break;
      }
    }

    if (i >= lhsChildren.size()) {
      break;
    }

    for (; j < rhsChildren.size(); j++) {
      if (is<Variable>(rhsChildren[j])) {
        break;
      }
      if (auto rhsChildExpr = cast<IExpression>(rhsChildren[j]);
          rhsChildExpr && !rhsChildExpr->getVariables().empty()) {
        break;
      }
    }

    if (j >= rhsChildren.size()) {
      break;
    }

    if (int res = comparator(lhsChildren[i], rhsChildren[j]); res != 0) {
      return res;
    }
  }

  for (size_t i = 0; i < std::min(lhsChildren.size(), rhsChildren.size()); i++) {
    if (int res = comparator(lhsChildren[i], rhsChildren[i]); res != 0) {
      return res;
    }
  }

  if (lhsChildren.size() == rhsChildren.size()) {
    return 0;
  }

  return lhsChildren.size() > rhsChildren.size() ? -1 : 1;
}

int IPolynomExpression::comparatorFunctions(const std::shared_ptr<const IExpression> &lhsExpr,
                                            const std::shared_ptr<const IExpression> &rhsExpr) const {

  if (!lhsExpr && !rhsExpr) {
    return 0;
  }

  if (lhsExpr && rhsExpr) {
    auto lhsFunc = lhsExpr->getFunction();
    auto rhsFunc = rhsExpr->getFunction();

    {
      ArgumentsPtrVector lhsChildren = lhsExpr->getChildren();
      ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

      ArgumentPtr lhsChild = nullptr;
      ArgumentPtr rhsChild = nullptr;

      if (lhsChildren.size() == 1) {
        lhsChild = lhsChildren.front();
      }
      if (rhsChildren.size() == 1) {
        rhsChild = rhsChildren.front();
      }

      if (lhsChild || rhsChild) {
        if (!lhsChild) {
          lhsChild = lhsExpr;
        }
        else if (!rhsChild) {
          rhsChild = rhsExpr;
        }

        if (int res = comparator(lhsChild, rhsChild); res != 0) {
          return res;
        }
      }
      else if (*lhsFunc == *rhsFunc) {
        return comparatorChildren(lhsChildren, rhsChildren);
      }
    }

    if (auto lhsOper = cast<IOperator>(lhsFunc)) {
      if (auto rhsOper = cast<IOperator>(rhsFunc)) {
        return lhsOper->toString() < rhsOper->toString() ? -1 : 1;
      }

      return -1;
    }

    if (is<IOperator>(rhsFunc)) {
      return 1;
    }

    return lhsFunc->toString() < rhsFunc->toString() ? -1 : 1;
  }

  return 0;
}

}
