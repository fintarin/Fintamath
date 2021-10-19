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
private:
  Fraction toFrac(const std::shared_ptr<Tree::Node> &) const;
  void solveRec(std::shared_ptr<Tree::Node> &);

public:
  Fraction solve(Tree &);
  void solveEquals(const std::vector<std::string> &, const Fraction &);
  std::vector<Param> getParams();

private:
  std::vector<Param> params;
};

#endif // SOLVER_HPP