#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include <string>
#include <vector>

#include "expressions/Expression.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

struct Param {
  std::string name;
  Rational value;
};

class Solver {
public:
  Rational solve(Expression &);

  int64_t getPrecision() const;
  void setPrecision(int64_t precision);

private:
  const int64_t initialPrecision = 36;

  std::vector<Param> params;
  int64_t precision = initialPrecision;

  Rational toFrac(const std::shared_ptr<Expression::Elem> &) const;
  void solveRec(std::shared_ptr<Expression::Elem> &);

  int64_t getNewPrecision() const;
  int64_t getNewRoundPrecision() const;
};

#endif // SOLVER_HPP