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

static void rootReset(const shared_ptr<Expression::Elem> &root, const Rational &inFrac);

Rational Solver::solve(Expression &Expression) {
  if (Expression.getRootModifiable()->right->right == nullptr &&
      Expression.getRootModifiable()->right->left == nullptr) {
    return Rational(toFrac(Expression.getRootModifiable()->right).toString());
  }
  solveRec(Expression.getRootModifiable()->right);
  return *dynamic_pointer_cast<Rational>(Expression.getRootModifiable()->right->info);
}

int64_t Solver::getPrecision() const {
  return precision;
}

void Solver::setPrecision(int64_t precision) {
  this->precision = precision;
}

Rational Solver::toFrac(const shared_ptr<Expression::Elem> &root) const {
  if (root->info == nullptr) {
    throw invalid_argument("Parser invalid input");
  }

  if (root->info->getTypeName() == "Constant") {
    return Constant(root->info->toString()).toRational(getNewPrecision());
  }

  try {
    return *dynamic_pointer_cast<Rational>(root->info);
  } catch (const invalid_argument &) {
    throw invalid_argument("Solver invalid input");
  }
}

void Solver::solveRec(shared_ptr<Expression::Elem> &root) {
  if (root->info == nullptr) {
    throw invalid_argument("Parser invalid input");
  }
  if (root->right != nullptr) {
    if (root->right->info == nullptr) {
      throw invalid_argument("Parser invalid input");
    }
    if (root->right->info->getTypeName() == "Operator" || root->right->info->getTypeName() == "Function") {
      solveRec(root->right);
    }
  }
  if (root->left != nullptr) {
    if (root->left->info == nullptr) {
      throw invalid_argument("Parser invalid input");
    }
    if (root->left->info->getTypeName() == "Operator" || root->left->info->getTypeName() == "Function") {
      solveRec(root->left);
    }
  }
  if (root->info->getTypeName() == "Operator") {
    Operator oper(root->info->toString());
    Rational frac(
        oper.solve(toFrac(root->right), toFrac(root->left), getNewPrecision()).toString(getNewRoundPrecision()));
    rootReset(root, frac);
    return;
  }
  if (root->info->getTypeName() == "Function") {
    Function func(root->info->toString());
    Rational frac;
    if (isType::isBinaryFunction(func.toString())) {
      frac = Rational(
          func.solve(toFrac(root->right), toFrac(root->left), getNewPrecision()).toString(getNewRoundPrecision()));
    } else {
      frac = Rational(func.solve(toFrac(root->right), getNewPrecision()).toString(getNewRoundPrecision()));
    }
    rootReset(root, frac);
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

static void rootReset(const shared_ptr<Expression::Elem> &root, const Rational &inFrac) {
  root->info = make_shared<Rational>(inFrac);
  root->right.reset();
  root->left.reset();
}
