#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

class Operator : public ISingleEntity {
public:
  explicit Operator(const std::string &);

  bool isEqualSign() const;
  Rational solve(const Rational &, const Rational &, int64_t) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  char oper;
};

namespace isType {
bool isOperator(const std::string &);
}

#endif // OPERATOR_HPP