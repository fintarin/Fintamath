#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

IPolynomExpression::IPolynomExpression(const IPolynomExpression &rhs) : polynomVect(rhs.clonePolynom()) {
}

IPolynomExpression &IPolynomExpression::operator=(const IPolynomExpression &rhs) {
  if (&rhs != this) {
    polynomVect = rhs.clonePolynom();
  }
  return *this;
}

IPolynomExpression::IPolynomExpression(PolynomVector inPolynomVect) : polynomVect(std::move(inPolynomVect)) {
}

void IPolynomExpression::pushPolynomToPolynom(const PolynomVector &from, PolynomVector &to) {
  for (const auto &elem : from) {
    to.emplace_back(elem->clone());
  }
}

const IPolynomExpression::PolynomVector &IPolynomExpression::getPolynomVector() const {
  return clonePolynom();
}

void IPolynomExpression::setPrecision(uint8_t precision) {
  for (auto &child : polynomVect) {
    if (auto *expr = cast<IExpression>(child.get())) {
      expr->setPrecision(precision);
      child = MathObjectPtr(expr);
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

IPolynomExpression::PolynomVector IPolynomExpression::clonePolynom() const {
  PolynomVector clonedVector;
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

}