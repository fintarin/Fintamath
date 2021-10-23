#include "calculator/Solver.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "single_entities/operators/Function.hpp"
#include "single_entities/operators/Operator.hpp"
#include "single_entities/terms/literals/Constant.hpp"

using namespace std;

static void elemReset(const shared_ptr<Expression::Elem> &elem, const Rational &val);

Rational Solver::solve(Expression &expr) {
  if (expr.getRootModifiable()->right->right == nullptr && expr.getRootModifiable()->right->left == nullptr) {
    return Rational(toRational(expr.getRootModifiable()->right).toString());
  }
  solveRec(expr.getRootModifiable()->right);
  return *dynamic_pointer_cast<Rational>(expr.getRootModifiable()->right->info);
}

int64_t Solver::getPrecision() const {
  return precision;
}

void Solver::setPrecision(int64_t precision_) {
  this->precision = precision_;
}

Rational Solver::toRational(const shared_ptr<Expression::Elem> &elem) const {
  if (elem->info == nullptr) {
    throw invalid_argument("Solver invalid input");
  }

  if (elem->info->getTypeName() == "Constant") {
    return Constant(elem->info->toString()).toRational(getNewPrecision());
  }

  try {
    return *dynamic_pointer_cast<Rational>(elem->info);
  } catch (const invalid_argument &) {
    throw invalid_argument("Solver invalid input");
  }
}

void Solver::solveRec(const shared_ptr<Expression::Elem> &elem) {
  if (elem->info == nullptr) {
    throw invalid_argument("Solver invalid input");
  }

  if (elem->right != nullptr) {
    if (elem->right->info == nullptr) {
      throw invalid_argument("Solver invalid input");
    }
    if (elem->right->info->getTypeName() == "Operator" || elem->right->info->getTypeName() == "Function") {
      solveRec(elem->right);
    }
  }

  if (elem->left != nullptr) {
    if (elem->left->info == nullptr) {
      throw invalid_argument("Solver invalid input");
    }
    if (elem->left->info->getTypeName() == "Operator" || elem->left->info->getTypeName() == "Function") {
      solveRec(elem->left);
    }
  }

  if (elem->info->getTypeName() == "Operator") {
    Operator oper(elem->info->toString());
    Rational val(oper.solve(toRational(elem->right), toRational(elem->left), getNewPrecision())
                     .toString(getNewRoundPrecision()));
    elemReset(elem, val);
    return;
  }

  if (elem->info->getTypeName() == "Function") {
    Function func(elem->info->toString());
    Rational val;
    if (types::isBinaryFunction(func.toString())) {
      val = Rational(func.solve(toRational(elem->right), toRational(elem->left), getNewPrecision())
                         .toString(getNewRoundPrecision()));
    } else {
      val = Rational(func.solve(toRational(elem->right), getNewPrecision()).toString(getNewRoundPrecision()));
    }
    elemReset(elem, val);
    return;
  }
}

int64_t Solver::getNewPrecision() const {
  const int64_t PRECISION_INCREASER = 9;
  return precision + PRECISION_INCREASER;
}

int64_t Solver::getNewRoundPrecision() const {
  return getNewPrecision() - 1;
}

static void elemReset(const shared_ptr<Expression::Elem> &elem, const Rational &val) {
  elem->info = make_shared<Rational>(val);
  elem->right.reset();
  elem->left.reset();
}
