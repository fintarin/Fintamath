#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "expressions/Expression.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

struct Param {
  std::string name;
  Rational value;
};

class Solver {
public:
  Rational solve(Expression &expr);

  int64_t getPrecision() const;
  void setPrecision(int64_t precision_);

private:
  const int64_t initialPrecision = 36;

  std::vector<Param> params;
  int64_t precision = initialPrecision;

  Rational toRational(const std::shared_ptr<Expression::Elem> &elem) const;
  void solveRec(const std::shared_ptr<Expression::Elem> &elem);

  int64_t getNewPrecision() const;
  int64_t getNewRoundPrecision() const;
};

#endif // SOLVER_HPP