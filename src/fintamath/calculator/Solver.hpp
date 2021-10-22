#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include <string>
#include <vector>

#include "calculator/Expression.hpp"
#include "numbers/Rational.hpp"

struct Param {
  std::string name;
  Rational value;
};

class Solver {
public:
  Rational solve(Expression &);
  void solveEquals(const std::vector<std::string> &, const Rational &);

private:
  std::vector<Param> params;

  Rational toFrac(const std::shared_ptr<Expression::Elem> &) const;
  void solveRec(std::shared_ptr<Expression::Elem> &);
};

#endif // SOLVER_HPP