#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include <string>
#include <vector>

#include "calculator/Tree.hpp"
#include "numbers/Fraction.hpp"

struct Param {
  std::string name;
  Fraction value;
};

class Solver {
public:
  Fraction solve(Tree &);
  void solveEquals(const std::vector<std::string> &, const Fraction &);

private:
  std::vector<Param> params;

  Fraction toFrac(const std::shared_ptr<Tree::Node> &) const;
  void solveRec(std::shared_ptr<Tree::Node> &);
};

#endif // SOLVER_HPP