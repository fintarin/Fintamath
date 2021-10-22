#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

class Function : public ISingleEntity {
public:
  explicit Function(const std::string &);

  Rational solve(const Rational &) const;
  Rational solve(const Rational &, const Rational &) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  std::string func;
};

namespace isType {
bool isFunction(const std::string &);
bool isBinaryFunction(const std::string &);
} // namespace isType

#endif // FUNCTION_HPP
