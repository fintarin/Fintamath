#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

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

// void IPolynomExpression::setPrecision(uint8_t precision) {
//   for (auto &child : children) {
//     if (auto expr = cast<IExpression>(child)) {
//       expr->setPrecision(precision);
//       return;
//     }

//     if (const auto constant = cast<IConstant>(child)) {
//       child = (*constant)();
//     }

//     if (is<INumber>(child)) {
//       child = make_shared<Real>(convert<Real>(*child).precise(precision));
//     }
//   }
// }

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
  // {
  //   shared_ptr<IPolynomExpression> simplExpr = cast<IPolynomExpression>(simpl->clone());
  //   ArgumentsPtrVector oldChildren = simplExpr->children;
  //   simplExpr->children.clear();

  //   for (auto &child : oldChildren) {
  //     simplifyChild(child);
  //     simplExpr->addElement(child);
  //   }

  //   simpl = simplExpr;
  // }
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
      if (func->isNonExressionEvaluatable() && func->doArgsMatch({*children[i], *children[j]})) {
        children[i] = (*func)(*children[i], *children[j]);
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

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }
  return simpl;
}

// void IPolynomExpression::sortVector(ArgumentsPtrVector &vector,
//                                     map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
//                                     ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector) {
//   for (auto &child : vector) {
//     if (const auto expr = cast<IExpression>(child)) {
//       if (const auto op = cast<IOperator>(expr->getFunction())) {
//         priorityMap[op->getOperatorPriority()].emplace_back(child);
//         continue;
//       }
//       functionVector.emplace_back(child);
//       continue;
//     }

//     if (is<Variable>(child)) {
//       variableVector.emplace_back(child);
//     }
//   }
// }
}