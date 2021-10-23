#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

class Function : public ISingleEntity {
public:
  explicit Function(const std::string &strFunc);

  Rational solve(const Rational &rhs, int64_t precision) const;
  Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  std::string name;
};

namespace types {
bool isFunction(const std::string &str);
bool isBinaryFunction(const std::string &str);
} // namespace types

#endif // FUNCTION_HPP
