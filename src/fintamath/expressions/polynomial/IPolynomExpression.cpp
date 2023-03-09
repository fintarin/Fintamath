#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

IPolynomExpression::IPolynomExpression(const IPolynomExpression &rhs) : polynomVect(rhs.getPolynom()) {
}

IPolynomExpression &IPolynomExpression::operator=(const IPolynomExpression &rhs) {
  if (&rhs != this) {
    polynomVect = rhs.getPolynom();
  }
  return *this;
}

IPolynomExpression::IPolynomExpression(ArgumentsPtrVector &&inPolynomVect) : polynomVect(std::move(inPolynomVect)) {
}

void IPolynomExpression::pushPolynomToPolynom(ArgumentsPtrVector &&from, ArgumentsPtrVector &to) {
  for (auto &elem : from) {
    to.emplace_back(std::move(elem));
  }
}

const ArgumentsPtrVector &IPolynomExpression::getArgumentsPtrVector() const {
  return polynomVect;
}

void IPolynomExpression::setPrecision(uint8_t precision) {
  for (auto &child : polynomVect) {
    if (auto *expr = cast<IExpression>(child.get())) {
      expr->setPrecision(precision);
      return;
    }

    if (const auto *constant = cast<IConstant>(child.get())) {
      child = (*constant)();
    }

    if (is<INumber>(child)) {
      child = convert<Real>(*child).precise(precision).clone();
    }
  }
}

std::vector<MathObjectPtr> IPolynomExpression::getVariables() const {
  std::vector<MathObjectPtr> vars;

  for (const auto &child : polynomVect) {
    if (is<Variable>(child)) {
      vars.emplace_back(child->clone());
      continue;
    }

    if (const auto *childExpr = cast<IExpression>(child.get())) {
      auto childVars = childExpr->getVariables();

      for (const auto &childVar : childVars) {
        vars.emplace_back(childVar->clone());
      }

      continue;
    }
  }

  return vars;
}

ArgumentsPtrVector IPolynomExpression::getPolynom() const {
  ArgumentsPtrVector clonedVector;

  for (const auto &elem : polynomVect) {
    clonedVector.emplace_back(elem->clone());
  }

  return clonedVector;
}

// TODO: remove this
void IPolynomExpression::validate() const {
  for (const auto &child : polynomVect) {
    if (const auto *childExpr = cast<IExpression>(child.get())) {
      childExpr->validate();
    }
  }

  const IFunction *func = this->getFunction();

  for (size_t i = 1; i < polynomVect.size(); i++) {
    this->validateArgs(*func, {*polynomVect[i - 1], *polynomVect[i]});
  }
}

void IPolynomExpression::sortVector(ArgumentsPtrVector &vector,
                                    std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                                    ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector) {
  for (auto &child : vector) {
    if (const auto *expr = cast<IExpression>(child.get())) {
      const auto *func = expr->getFunction();
      if (const auto *op = cast<IOperator>(func)) {
        priorityMap[op->getOperatorPriority()].emplace_back(std::move(child));
        continue;
      }
      functionVector.emplace_back(std::move(child));
      continue;
    }

    if (is<Variable>(child)) {
      variableVector.emplace_back(std::move(child));
    }
  }
}

}