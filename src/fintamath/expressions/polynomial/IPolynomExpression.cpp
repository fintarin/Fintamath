#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

// void IPolynomExpression::pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to) {
//   for (const auto &elem : from) {
//     to.emplace_back(elem);
//   }
// }

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

string IPolynomExpression::childToString(const ArgumentPtr &child, bool isFirst) const {
  return {};
}

ArgumentsPtrVector IPolynomExpression::getVariables() const {
  ArgumentsPtrVector vars;

  for (const auto &child : children) {
    if (is<Variable>(child)) {
      vars.emplace_back(child);
    }
    else if (const auto childExpr = cast<IExpression>(child)) {
      auto childVars = childExpr->getVariables();

      for (const auto &childVar : childVars) {
        vars.emplace_back(childVar);
      }
    }
  }

  return vars;
}

ArgumentsPtrVector IPolynomExpression::getPolynom() const {
  return children;
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
  std::sort(simpl->children.begin(), simpl->children.end(), [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return comparator(lhs, rhs);
  });

  simpl->postSortProcessing();

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

bool IPolynomExpression::comparator(const ArgumentPtr &left, const ArgumentPtr &right) const {
  auto leftExpr = cast<IExpression>(left);
  auto rightExpr = cast<IExpression>(right);
  if (leftExpr && rightExpr) {
    auto leftFunction = leftExpr->getFunction();
    auto rightFunction = rightExpr->getFunction();
    if (!is<IOperator>(leftFunction) && !is<IOperator>(rightFunction)) {
      return functionComparator(left, right);
    }

    return operatorComparator(left, right);
  }

  if (!leftExpr && !rightExpr) {
    return literalComparator(left, right);
  }

  return powComparator(left, right);
}

bool IPolynomExpression::operatorComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto leftExpr = cast<IExpression>(lhs);
  auto rightExpr = cast<IExpression>(rhs);
  auto leftOp = cast<IOperator>(leftExpr->getFunction());
  auto rightOp = cast<IOperator>(rightExpr->getFunction());

  if (!leftOp) {
    return false;
  }

  if (!rightOp) {
    return true;
  }

  if (leftOp->getOperatorPriority() == rightOp->getOperatorPriority()) {
    if (leftOp->getOperatorPriority() == IOperator::Priority::Exponentiation) {
      return powComparator(lhs, rhs);
    }
    return leftExpr->getChildren()[0]->toString() < rightExpr->getChildren()[0]->toString();
  }

  return leftOp->getOperatorPriority() < rightOp->getOperatorPriority();
}

bool IPolynomExpression::literalComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto leftLit = cast<ILiteral>(lhs);
  auto rightLit = cast<ILiteral>(rhs);

  if (!leftLit && !rightLit) {
    return lhs->toString() < rhs->toString();
  }

  if (!leftLit) {
    return false;
  }

  if (!rightLit) {
    return true;
  }

  auto leftConst = cast<IConstant>(lhs);
  auto rightConst = cast<IConstant>(rhs);

  if ((!leftConst || rightConst) && (!rightConst || leftConst)) { // logic equivalent operator (leftConst <->
                                                                  // rightConst)
    return lhs->toString() < rhs->toString();
  }

  if (!leftConst) {
    return true;
  }

  if (!rightConst) {
    return false;
  }
}

bool IPolynomExpression::powComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto leftExpr = cast<IExpression>(lhs);
  auto rightExpr = cast<IExpression>(rhs);

  if (!leftExpr || !rightExpr) {
    return rightExpr == nullptr;
  }

  if (leftExpr->getChildren()[0]->toString() == rightExpr->getChildren()[0]->toString()) {
    return leftExpr->getChildren()[1]->toString() > rightExpr->getChildren()[1]->toString();
  }

  return leftExpr->getChildren()[0]->toString() < rightExpr->getChildren()[0]->toString();
}

bool IPolynomExpression::functionComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto leftExpr = cast<IExpression>(lhs);
  auto rightExpr = cast<IExpression>(rhs);
  auto leftFunction = leftExpr->getFunction();
  auto rightFunction = rightExpr->getFunction();

  if (leftFunction->toString() == rightFunction->toString()) {
    return comparator(leftExpr->getChildren()[0], rightExpr->getChildren()[0]);
  }

  return leftFunction->toString() < rightFunction->toString();
}

void IPolynomExpression::sort() {
  std::sort(children.begin(), children.end(), [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return comparator(lhs, rhs);
  });
  postSortProcessing();
}

void IPolynomExpression::postSortProcessing() {
}
}