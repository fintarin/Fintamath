#include "calculator/Solver.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "calculator/Calculator.hpp"
#include "numbers/Constant.hpp"
#include "numbers/Variable.hpp"
#include "operators/Function.hpp"
#include "operators/Operator.hpp"

using namespace std;

void rootReset(const shared_ptr<Tree::Node> &root, const Fraction &inFrac);

Fraction Solver::solve(Tree &tree) {
  if (tree.root->right->right == nullptr && tree.root->right->left == nullptr) {
    return Fraction(toFrac(tree.root->right).toString());
  }
  solveRec(tree.root->right);
  return *dynamic_pointer_cast<Fraction>(tree.root->right->info);
}

void Solver::solveEquals(const vector<string> &vectIOfTokens, const Fraction &inFrac) {
  if (vectIOfTokens.size() < 2) {
    throw invalid_argument("Parser invalid input");
  }
  if (!(isType::isVariable(*(vectIOfTokens.end() - 1)))) {
    throw invalid_argument("Parser invalid input");
  }

  for (size_t i = 1; i < vectIOfTokens.size(); ++i) {
    if (vectIOfTokens[i] == "=" && !isType::isVariable(vectIOfTokens[i + 1])) {
      throw invalid_argument("Parser invalid input");
    }

    if (isType::isVariable(vectIOfTokens[i])) {
      if (!(vectIOfTokens[i - 1] == "=")) {
        throw invalid_argument("Parser invalid input");
      }
      if (isType::isConstant(vectIOfTokens[i]) || isType::isFunction(vectIOfTokens[i])) {
        throw invalid_argument("Solver invalid input");
      }

      size_t j = 0;
      for (; j < this->params.size(); ++j) {
        if (this->params[j].name == vectIOfTokens[i]) {
          this->params[j].value = inFrac;
          break;
        }
      }

      if (j == this->params.size()) {
        Param par;
        par.name = vectIOfTokens[i];
        par.value = inFrac;
        this->params.push_back(par);
      }
    }
  }
}

Fraction Solver::toFrac(const shared_ptr<Tree::Node> &root) const {
  if (root->info == nullptr) {
    throw invalid_argument("Parser invalid input");
  }

  if (root->info->getTypeName() == "Constant") {
    return Fraction(root->info->toString());
  }

  if (root->info->getTypeName() == "Variable") {
    string str = root->info->toString();
    auto iter = find_if(this->params.begin(), this->params.end(), [str](const Param &p) { return p.name == str; });
    if (iter == this->params.end()) {
      throw invalid_argument("Solver invalid input");
    }
    return iter->value;
  }

  try {
    return *dynamic_pointer_cast<Fraction>(root->info);
  } catch (const invalid_argument &) {
    throw invalid_argument("Solver invalid input");
  }
}

void Solver::solveRec(shared_ptr<Tree::Node> &root) {
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
    Fraction frac = oper.solve(toFrac(root->right), toFrac(root->left));
    rootReset(root, frac);
    return;
  }
  if (root->info->getTypeName() == "Function") {
    Function func(root->info->toString());
    Fraction frac;
    if (isType::isBinaryFunction(func.toString())) {
      frac = func.solve(toFrac(root->right), toFrac(root->left)).round(PRECISION + ROUND_CONST / 2);
    } else {
      frac = func.solve(toFrac(root->right)).round(PRECISION + ROUND_CONST / 2);
    }
    rootReset(root, frac);
    return;
  }
}

inline void rootReset(const shared_ptr<Tree::Node> &root, const Fraction &inFrac) {
  root->info = make_shared<Fraction>(inFrac);
  root->right.reset();
  root->left.reset();
}
