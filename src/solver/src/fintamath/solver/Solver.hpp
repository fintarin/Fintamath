#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "fintamath/math_objects/nodes/expressions/ArithmeticExpression.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

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
  Rational solve(ArithmeticExpression &expr);

  int64_t getPrecision() const;
  void setPrecision(int64_t precision_);

private:
  const int64_t initialPrecision = 36;

  std::vector<Param> params;
  int64_t precision = initialPrecision;

  Rational toRational(const std::shared_ptr<ArithmeticExpression::Elem> &elem) const;
  void solveRec(const std::shared_ptr<ArithmeticExpression::Elem> &elem);

  int64_t getNewPrecision() const;
  int64_t getNewRoundPrecision() const;
};

#endif // SOLVER_HPP
