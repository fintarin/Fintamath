#ifndef ARITHMETICOPERATOR_HPP
#define ARITHMETICOPERATOR_HPP

#include "fintamath/math_objects/relations/operators/Operator.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

class ArithmeticOperator : public Operator {
public:
  explicit ArithmeticOperator(const std::string &strOper);

  Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  char name;
};

namespace types {
bool isOperator(const std::string &str);
}

#endif // ARITHMETICOPERATOR_HPP
