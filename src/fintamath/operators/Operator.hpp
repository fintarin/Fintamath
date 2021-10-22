#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>

#include "calculator/ISingleEntity.hpp"
#include "numbers/Rational.hpp"

class Operator : public ISingleEntity {
public:
  explicit Operator(const std::string &);

  bool isEqualSign() const;
  Rational solve(const Rational &, const Rational &) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  char oper;
};

namespace isType {
bool isOperator(const std::string &);
}

#endif // OPERATOR_HPP