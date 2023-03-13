#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

void IPolynomExpression::pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to) {
  for (const auto &elem : from) {
    to.emplace_back(elem);
  }
}

std::shared_ptr<IFunction> IPolynomExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IPolynomExpression::getChildren() const {
  return children;
}

void IPolynomExpression::setPrecision(uint8_t precision) {
  for (auto &child : children) {
    if (auto expr = cast<IExpression>(child)) {
      expr->setPrecision(precision);
      return;
    }

    if (const auto constant = cast<IConstant>(child)) {
      child = (*constant)();
    }

    if (is<INumber>(child)) {
      child = std::make_shared<Real>(convert<Real>(*child).precise(precision));
    }
  }
}

ArgumentsPtrVector IPolynomExpression::getVariables() const {
  ArgumentsPtrVector vars;

  for (const auto &child : children) {
    if (is<Variable>(child)) {
      vars.emplace_back(child);
      continue;
    }

    if (const auto childExpr = cast<IExpression>(child)) {
      auto childVars = childExpr->getVariables();

      for (const auto &childVar : childVars) {
        vars.emplace_back(childVar);
      }

      continue;
    }
  }

  return vars;
}

ArgumentsPtrVector IPolynomExpression::getPolynom() const {
  return children;
}

std::shared_ptr<IMathObject> IPolynomExpression::simplify() {
  preSimplifyRec();

  for (auto &child : children) {
    simplifyChild(child);
  }

  preSimplifyRec(); // TODO: try to remove this
  postSimplifyRec();

  if (children.size() == 1) {
    return children.front();
  }

  return {};
}

std::shared_ptr<IMathObject> IPolynomExpression::preSimplify(size_t /*lhsChildNum*/, size_t /*rhsChildNum*/) {
  return {};
}

std::shared_ptr<IMathObject> IPolynomExpression::postSimplify(size_t /*lhsChildNum*/, size_t /*rhsChildNum*/) {
  return {};
}

void IPolynomExpression::preSimplifyRec() {
  size_t childrenSize = children.size();

  for (int64_t i = 0; i < children.size() - 1; i++) {
    for (int64_t j = i + 1; j < children.size(); j++) {
      if (auto res = preSimplify(i, j)) {
        children[i] = res;
        children.erase(children.begin() + j);
        continue;
      }
    }
  }

  if (children.size() != childrenSize) {
    postSimplifyRec();
  }
}

void IPolynomExpression::postSimplifyRec() {
  size_t childrenSize = children.size();

  for (int64_t i = 0; i < children.size() - 1; i++) {
    for (int64_t j = i + 1; j < children.size(); j++) {
      if (func->isNonExressionEvaluatable() && func->doArgsMatch({*children[i], *children[j]})) {
        children[i] = (*func)(*children[i], *children[j]);
        children.erase(children.begin() + j);
        continue;
      }

      if (auto res = postSimplify(i, j)) {
        children[i] = res;
        children.erase(children.begin() + j);
        continue;
      }
    }
  }

  if (children.size() != childrenSize) {
    postSimplifyRec();
  }
}

void IPolynomExpression::validate() const {
  for (const auto &child : children) {
    if (const auto childExpr = cast<IExpression>(child)) {
      childExpr->validate();
    }
  }

  const auto func = this->getFunction();

  for (int64_t i = 0; i < children.size() - 1; i++) {
    for (int64_t j = i + 1; j < children.size(); j++) {
      validateChildren(*func, {children[i], children[j]});
    }
  }
}

void IPolynomExpression::sortVector(ArgumentsPtrVector &vector,
                                    std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                                    ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector) {
  for (auto &child : vector) {
    if (const auto expr = cast<IExpression>(child)) {
      if (const auto op = cast<IOperator>(expr->getFunction())) {
        priorityMap[op->getOperatorPriority()].emplace_back(child);
        continue;
      }
      functionVector.emplace_back(child);
      continue;
    }

    if (is<Variable>(child)) {
      variableVector.emplace_back(child);
    }
  }
}

}