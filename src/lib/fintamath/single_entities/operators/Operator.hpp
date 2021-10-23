#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <cstdint>
#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

class Operator : public ISingleEntity {
public:
  explicit Operator(const std::string &strOper);

  Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  char name;
};

namespace types {
bool isOperator(const std::string &str);
}

#endif // OPERATOR_HPP
